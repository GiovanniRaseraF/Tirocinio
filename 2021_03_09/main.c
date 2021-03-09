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
#define MAX_STR 20

void cleanString(char *str_buffer, int size){
    for(int i = 0; i < size; i++)
        if(str_buffer[i] == 13 || str_buffer[i] == 10)
            str_buffer[i] = 0;
}

/*
Return: State calculation
*/
char findState(int a, int b) {
	if (a < b)	return 'r';
	if (a == b) return 's';
	if (a > b)	return 'f';
	return 0;
}

int read_int_from_buffer(void *rx_buf,struct rpmsg_channel *app_chnl){
    int len, res = 0, result = 0;
    unsigned long size, *src;
    char str_buffer[MAX_STR];
    
    //Read and copy
    result = rpmsg_rtos_recv_nocopy(app_chnl->rp_ept, &rx_buf, &len, &src, -1);
    assert(len < sizeof(str_buffer));
    memcpy(str_buffer, rx_buf, len);
    str_buffer[len] = 0;

    //Crean
    for(int i = 0; i < MAX_STR; i++)
            if(str_buffer[i] == 13 || str_buffer[i] == 10)
                str_buffer[i] = 0;


}

static void StartStateMachine(void *pvParameters){
    int result = 0, value = 0, len = 0;
    struct remote_device *rdev = NULL;
    struct rpmsg_channel *app_chnl = NULL;
    
    void *rx_buf, *tx_buf;

    /* RPMSG Init as REMOTE */
    PRINTF("Starting Machine\n\r");
    result = rpmsg_rtos_init(0 /*REMOTE_CPU_ID*/, &rdev, RPMSG_MASTER, &app_chnl);
    assert(result == 0);
    PRINTF("Started\n\r");

    while(true){
        
        if(*str_buffer){
            value = atoi(str_buffer);
            PRINTF("%d\n\r", value);
            //PRINTF("%s\n\r", str_buffer);
        }

        memset(str_buffer, 0, sizeof(str_buffer));
 
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