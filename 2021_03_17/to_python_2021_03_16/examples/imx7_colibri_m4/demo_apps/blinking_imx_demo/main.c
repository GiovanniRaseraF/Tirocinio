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
//Colors
#define GPIO_LED_RED 	0
#define GPIO_LED_GREEN 	1
#define GPIO_LED_BLUE	2
#define NUM_OF_COLORS	3
typedef gpio_pin_action_t sLed;
static volatile uint8_t currentColor = GPIO_LED_RED, prevColor = GPIO_LED_BLUE;

//RED GREE BLUE Cynexo Specific
void RGB_Set(sLed sRED, sLed sGREEN, sLed sBLUE){
	GPIO_Ctrl_Led_Set(BOARD_GPIO_LED_CONFIG_RED,	sRED);
	GPIO_Ctrl_Led_Set(BOARD_GPIO_LED_CONFIG_GREEN,	sGREEN);
	GPIO_Ctrl_Led_Set(BOARD_GPIO_LED_CONFIG_BLUE, 	sBLUE);
}

/*
* Comments: Function to output real color to the led
*/
void ToggleTask(void *pvParameters){
	//Socket Comunication Specific
	int result = 0;//, len = 0;
    struct remote_device *rdev = NULL;
    struct rpmsg_channel *app_chnl = NULL;
    //char str_buffer[256];
    //void *rx_buf, *tx_buf;
    //unsigned long size, src;
	//PRINTF("\r\n!! Load Driver From Linux To Continue...\r\n");
	result = rpmsg_rtos_init(0 /*REMOTE_CPU_ID*/, &rdev, RPMSG_MASTER, &app_chnl);
    //assert(result == 0);

	//Main Loop
    while (true){
    	//Print color
    	if(currentColor != prevColor){
			switch(currentColor){
			case GPIO_LED_RED:
				PRINTF("\n\rled: RED");
				RGB_Set(LED_ON, LED_OFF, LED_OFF);

				break;
			case GPIO_LED_GREEN:
				PRINTF("\n\rled: GREEN");
				RGB_Set(LED_OFF, LED_ON, LED_OFF);

				break;
			case GPIO_LED_BLUE:
				PRINTF("\n\rled: BLUE");
				RGB_Set(LED_OFF, LED_OFF, LED_ON);

				break;
			default:
				PRINTF("\n\rError!!");
				return;
				break;
			}
			
			prevColor = currentColor;
    	}
    }
}

/*
* Comments: Funcition to change color info
*/
void SwitchTask(void *pvParameters){
	uint8_t numberOfTimes = 0;
	uint32_t currentTime = 0, prevTime = 0, deltaTime = 0;

    while (true){
        //PRINTF("\n\rM4: Press Button, current color: %d\n\r", currentColor);
        GPIO_Ctrl_WaitKeyPressed();

        switch(numberOfTimes){
        case 0:
        	currentTime = xTaskGetTickCount();
        	prevTime = currentTime;
        	deltaTime = 0;
        	break;
        case 1:
        	currentTime = xTaskGetTickCount();
        	deltaTime = currentTime - prevTime;

        	PRINTF("\n\rDelta Time: %d", deltaTime);
        	break;
        default:

        	PRINTF("\n\rError, no case for numberOfTimes (0, 1)");
        	return;
        }
        //Change time read
        numberOfTimes++;
        numberOfTimes %= 2;

        //Change color
        currentColor++;
        currentColor %= NUM_OF_COLORS;
    }
}

/*
 * MU Interrrupt ISR
 */
void BOARD_MU_HANDLER(void)
{
    /*
     * calls into rpmsg_handler provided by middleware
     */
    rpmsg_handler();
}


int main(void){
    /* Initialize board specified hardware. */
    hardware_init();
    //Hw_Timer_Init();
    //Log
    PRINTF("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\r================= To Python : 9.16 ==================\n\r");
	GPIO_Ctrl_Init();

    /* Create a the APP main task. */
    xTaskCreate(ToggleTask, "Toggle Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL);
    xTaskCreate(SwitchTask, "Switch Task", configMINIMAL_STACK_SIZE,NULL, tskIDLE_PRIORITY+2, NULL);

    /* Start FreeRTOS */
    vTaskStartScheduler();
    while (true);
}

