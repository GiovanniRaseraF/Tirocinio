#include <stdio.h>
#include "board.h"
#include "gpio_pins.h"
#include "gpio_imx.h"
#include "gpio_ctrl.h"
#include "debug_console_imx.h"
#include "rpmsg/rpmsg_rtos.h"
#include "FreeRTOS.h"
#include "task.h"
#include "gpt.h"
#include "semphr.h"
#include "string.h"
#include "mu_imx.h"
#include "rdc_semaphore.h"
#include <stdlib.h>
#define APP_TASK_STACK_SIZE 256
#define APP_MU_IRQ_PRIORITY 3
#define MAX_STR 10

/*
Return: State calculation
*/
char findState(int a, int b) {
	if (a < b)	return 'r';
	if (a == b) return 's';
	if (a > b)	return 'f';
	return 0;
}

int read_int_from_buffer(int *value, void *rx_buf, struct rpmsg_channel *app_chnl){
    int len = 0, result = 0;
    unsigned long *src = NULL;
    char str_buffer[MAX_STR];
    
    //Read and copy
    result = rpmsg_rtos_recv_nocopy(app_chnl->rp_ept, &rx_buf, &len, src, 0);
    assert(len < sizeof(str_buffer));
    memcpy(str_buffer, rx_buf, len);
    str_buffer[len] = 0;

     //Crean and controll
    for(int i = 0; i < MAX_STR; i++){
        if(str_buffer[i] == 13 || str_buffer[i] == 10){
            str_buffer[i] = 0;
        }
    }

    //Check empty
    if(!(*str_buffer)){
        result = rpmsg_rtos_recv_nocopy_free(app_chnl->rp_ept, rx_buf); 
        return 0;
    }

    //To int
    result = atoi(str_buffer);
    *value = result;

    result = rpmsg_rtos_recv_nocopy_free(app_chnl->rp_ept, rx_buf); 
    return 1;
}

static void StartStateMachine(void *pvParameters){
    int result = 0, prev_value = 0, value = 0, pi[2], position = 0, read_result = 0;
    struct remote_device *rdev = NULL;
    struct rpmsg_channel *app_chnl = NULL;
    char actual_state = 'i';
    void *rx_buf = NULL;//, *tx_buf;

    /* RPMSG Init as REMOTE */
    PRINTF("Starting Machine\n\r");
    result = rpmsg_rtos_init(0 /*REMOTE_CPU_ID*/, &rdev, RPMSG_MASTER, &app_chnl);
    assert(result == 0);
    PRINTF("--Started--\n\r");

    //Init: read first value
    while(read_result == 0)
        read_result = read_int_from_buffer(&prev_value, rx_buf, app_chnl);
    actual_state = 'i';
    position = 0;
    read_result = 0;
    
    //Machine Loop
    while(true){
        //Read value and change state
        while(read_result == 0)
            read_result = read_int_from_buffer(&value ,rx_buf, app_chnl);
        position++;
        read_result = 0;

        char new_state = findState(prev_value, value);
        
        //Chose states
        switch (actual_state) {
		case 'i':
			//Init
			switch (new_state) {
			case 'i': case 'f': case 's':
				break;
			case 'r':
				//Save rising
				actual_state = 'r';
				pi[0] = value;
                pi[1] = position;
				break;
            default:
                PRINTF("Errore");
                exit(1);
                break;
			}
			break;
        case 'r':
			//Rising
			switch (new_state) {
			case 'r':
				actual_state = 'r';
				pi[0] = value;
                pi[1] = position;
				break;
			case 's':
				actual_state = 's';
				//pi = { v[i], i };
				break;
			case 'f':
				actual_state = 'i';
				//TODO: Da mettere la comicazione inversa verlo il A7
                PRINTF("Peak: %d, Offset: %d\n\r", pi[0], pi[1]);
				break;
            default:
                PRINTF("Errore");
                exit(1);
                break;
			}
			break;
        case 's':
			//Stato still
			switch (new_state) {
			case 's':
				actual_state = 's';
				//pi = { v[i], i };
				break;
			case 'r':
				actual_state = 's';
				pi[0] = value;
                pi[1] = position;
				break;
			case 'f':
				actual_state = 'i';
				//TODO
                PRINTF("Peak: %d, Offset: %d\n\r", pi[0], pi[1]);
				break;
            default:
                PRINTF("Errore");
                exit(1);
            break;
        }
		case 'f':
			break;

        default:
            PRINTF("Errore");
            exit(1);
            break;
        }

        //Update
        prev_value = value;
    }
}

void BOARD_MU_HANDLER(void){
    rpmsg_handler();
}

int main(void){
    /* hardware initialiize, include RDC, IOMUX, Uart debug initialize */
    hardware_init();

    PRINTF("\n\r\n\r\n\r");
    PRINTF("============== State Machine : Spike ===============\n\r");
    
    /* GPIO module initialize, configure "LED" as output and button as interrupt mode. */
    GPIO_Ctrl_Init();
    MU_Init(BOARD_MU_BASE_ADDR);
    NVIC_SetPriority(BOARD_MU_IRQ_NUM, APP_MU_IRQ_PRIORITY);
    NVIC_EnableIRQ(BOARD_MU_IRQ_NUM);

    /* Create a demo task. */
    xTaskCreate(StartStateMachine, "StateMachine", APP_TASK_STACK_SIZE,
                NULL, tskIDLE_PRIORITY+1, NULL);

    /* Start FreeRTOS scheduler. */
    vTaskStartScheduler();
    while (true);
}

#if 0
        if(*str_buffer){
            PRINTF("INVIATA:%s\n", str_buffer);

            /* Create message */
            len = snprintf(str_buffer, sizeof(str_buffer),"STR=%s; KEY=%d\n",
                    str_buffer, key);

            key += 1;

            /* Release tx buffer */
            tx_buf = rpmsg_rtos_alloc_tx_buffer(app_chnl->rp_ept, &size);
            if(tx_buf == NULL)
            {
                PRINTF("\r\n ERROR = rpmsg_rtos_alloc_tx_buffer\r\n");
                continue;
            }

            /* Copy string to RPMsg tx buffer */
            memcpy(tx_buf, str_buffer, len);

            /* Send message... */
            result = rpmsg_rtos_send_nocopy(app_chnl->rp_ept, tx_buf, len, app_chnl->dst);
            if(result != 0)
            {
                PRINTF("\r\n ERROR = rpmsg_rtos_send_nocopy\r\n");
            }
            assert(result == 0);

            /* free rx buffer */
            result = rpmsg_rtos_recv_nocopy_free(app_chnl->rp_ept, rx_buf); 

            memset(str_buffer, 0, sizeof(str_buffer));
        }

        memset(str_buffer, 0, sizeof(str_buffer));
        #endif