#include <stdio.h>
#include <stdlib.h>
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
//#include "gpt_timer.c"
#define APP_TASK_STACK_SIZE 256

/*
 * APP decided interrupt priority
 */
#define APP_MU_IRQ_PRIORITY 3
//Colors
#define GPIO_LED_RED 	0
#define GPIO_LED_GREEN 	1
#define GPIO_LED_BLUE	2
#define NUM_OF_COLORS	3
typedef gpio_pin_action_t sLed;
static volatile uint8_t currentColor = GPIO_LED_RED, prevColor = GPIO_LED_BLUE;
int deltaTime = 0;
bool is_delta_time_set = false, delta_time_sent = true;

//RED GREE BLUE Cynexo Specific
void RGB_Set(sLed sRED, sLed sGREEN, sLed sBLUE){
	GPIO_Ctrl_Led_Set(BOARD_GPIO_LED_CONFIG_RED,	sRED);
	GPIO_Ctrl_Led_Set(BOARD_GPIO_LED_CONFIG_GREEN,	sGREEN);
	GPIO_Ctrl_Led_Set(BOARD_GPIO_LED_CONFIG_BLUE, 	sBLUE);
}

//Message to linux
int send_to_linux(struct rpmsg_channel *app_chnl, char *str_buffer){
	//Cannot sent to linux, channel missing
	if(app_chnl == NULL) {
		PRINTF("\n\r!! channel missing\n\r");
		return 0;
	}
	assert(app_chnl != NULL);
	
	void *tx_buf;
	unsigned long size;
	int len = strlen(str_buffer), result = 0;
	
	/* Release tx buffer */
	tx_buf = rpmsg_rtos_alloc_tx_buffer(app_chnl->rp_ept, &size);
	if(tx_buf == NULL){
		PRINTF("\n\r!! tx_buf allocation error: tx_buf = rpmsg_rtos_alloc_tx_buffer(app_chnl->rp_ept, &size);\n\r");
		return 0;
	}
	assert(tx_buf != NULL);

	memcpy(tx_buf, str_buffer, size);

	/* Send */
	result = rpmsg_rtos_send(app_chnl->rp_ept, tx_buf, len, app_chnl->dst);
	if(result != 0){
		PRINTF("\n\r!! sent tx_buffer failed: result = rpmsg_rtos_send(app_chnl->rp_ept, tx_buf, len, app_chnl->dst);\n\r");
		return 0;
	}
	assert(result == 0);

	return 1;
}

/*
* Comments: Function to output real color to the led
*/
void ToggleTask(void *pvParameters){
	//Socket Comunication Specific
	int result = 0;
    struct remote_device *rdev = NULL;
    struct rpmsg_channel *app_chnl = NULL;
    char str_buffer[50];
	
	PRINTF("\r\n!! Load Driver From Linux To Continue...\r\n");
	result = rpmsg_rtos_init(0 /*REMOTE_CPU_ID*/, &rdev, RPMSG_MASTER, &app_chnl);
    assert(result == 0);
	PRINTF("\r\n!! Driver Loaded...\r\n");

	//Main Loop
    while (true){
    	//Print color ad send it to linux
    	if(currentColor != prevColor){
			switch(currentColor){
			case GPIO_LED_RED:
				//PRINTF("\n\rled: RED");
				RGB_Set(LED_ON, LED_OFF, LED_OFF);
				//send_to_linux(app_chnl, "\nled: RED");

				break;
			case GPIO_LED_GREEN:
				//PRINTF("\n\rled: GREEN");
				RGB_Set(LED_OFF, LED_ON, LED_OFF);
				//send_to_linux(app_chnl, "\nled: GREEN");

				break;
			case GPIO_LED_BLUE:
				//PRINTF("\n\rled: BLUE");
				RGB_Set(LED_OFF, LED_OFF, LED_ON);
				//send_to_linux(app_chnl, "\nled: BLUE");

				break;
			default:
				PRINTF("\n\rError!!");
				return;
				
				break;
			}
			prevColor = currentColor;

    	}

		//Comunicate delta time
		if(!delta_time_sent && is_delta_time_set){
			snprintf(str_buffer, sizeof(str_buffer), "delta_Time:%d\n", deltaTime);
			send_to_linux(app_chnl, str_buffer);
			
			delta_time_sent = true;
		}
    }
}

/*
* Comments: Funcition to change color info
*/
void SwitchTask(void *pvParameters){
	uint8_t numberOfTimes = 0;
	uint32_t currentTime = 0, prevTime = 0;

    while (true){
        //PRINTF("\n\rM4: Press Button, current color: %d\n\r", currentColor);
        GPIO_Ctrl_WaitKeyPressed();
		
        switch(numberOfTimes){
        case 0:
			PRINTF("\n\rFirst Click;");
        	currentTime = xTaskGetTickCount();
        	prevTime = currentTime;
        	deltaTime = 0;
			is_delta_time_set = false;

        	break;
        case 1:
        	currentTime = xTaskGetTickCount();
        	deltaTime = currentTime - prevTime;
			is_delta_time_set = true;
			delta_time_sent = false;
        	PRINTF("\n\rSecond Click; Delta Time: %d", deltaTime);

        	break;
        default:
        	PRINTF("\n\rError, no case for numberOfTimes (0, 1)");
			return;

			break;
        }
        //Change time read
        numberOfTimes++;
        numberOfTimes %= 2;

        //Change color
        currentColor++;
        currentColor %= NUM_OF_COLORS;
    }
}

/* MU Interrrupt ISR */
void BOARD_MU_HANDLER(void){rpmsg_handler();}

int main(void){
    /* Initialize board specified hardware. */
    hardware_init();
    MU_Init(BOARD_MU_BASE_ADDR);
    NVIC_SetPriority(BOARD_MU_IRQ_NUM, APP_MU_IRQ_PRIORITY);
    NVIC_EnableIRQ(BOARD_MU_IRQ_NUM);
    //Hw_Timer_Init();

    //Log
    PRINTF("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\r================= To Python : 12.24 ==================\n\r");
	GPIO_Ctrl_Init();

    /* Create a the APP main task. */
    xTaskCreate(ToggleTask, "MessageToLinux", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL);
    xTaskCreate(SwitchTask, "SwitchListening", configMINIMAL_STACK_SIZE,NULL, tskIDLE_PRIORITY+2, NULL);

    /* Start FreeRTOS */
    vTaskStartScheduler();
    while (true);
}

