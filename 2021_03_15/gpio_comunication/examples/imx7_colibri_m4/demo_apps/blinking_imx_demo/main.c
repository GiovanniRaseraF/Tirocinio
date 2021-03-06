#include "FreeRTOS.h"
#include "task.h"
#include "board.h"
#include "debug_console_imx.h"
#include "gpio_ctrl.h"
#include "hw_timer.h"
//Colors
#define GPIO_LED_RED 	0
#define GPIO_LED_GREEN 	1
#define GPIO_LED_BLUE	2
#define NUM_OF_COLORS	3
static volatile uint8_t currentColor = GPIO_LED_RED, prevColor = GPIO_LED_BLUE;

//#define BOARD_GPIO_LED_CONFIG_GREEN             (&gpioLed_CynexoRGBLed_Green)
//#define BOARD_GPIO_LED_CONFIG_RED               (&gpioLed_CynexoRGBLed_Red)
//#define BOARD_GPIO_LED_CONFIG_BLUE              (&gpioLed_CynexoRGBLed_Blue)

/*
* Comments: Function to output real color to the led
*/
void ToggleTask(void *pvParameters){
	//bool is_on = false;
    while (true){
    	//Print color
    	if(currentColor != prevColor){
			switch(currentColor){
			case GPIO_LED_RED:
				PRINTF("\n\rled: RED");
				GPIO_Ctrl_Led_ON(BOARD_GPIO_LED_CONFIG_RED);
				GPIO_Ctrl_Led_OFF(BOARD_GPIO_LED_CONFIG_BLUE);
				GPIO_Ctrl_Led_OFF(BOARD_GPIO_LED_CONFIG_GREEN);
				break;
			case GPIO_LED_GREEN:
				PRINTF("\n\rled: GREEN");
				GPIO_Ctrl_Led_OFF(BOARD_GPIO_LED_CONFIG_RED);
				GPIO_Ctrl_Led_OFF(BOARD_GPIO_LED_CONFIG_BLUE);
				GPIO_Ctrl_Led_ON(BOARD_GPIO_LED_CONFIG_GREEN);
				break;

			case GPIO_LED_BLUE:
				PRINTF("\n\rled: BLUE");
				GPIO_Ctrl_Led_OFF(BOARD_GPIO_LED_CONFIG_RED);
				GPIO_Ctrl_Led_ON(BOARD_GPIO_LED_CONFIG_BLUE);
				GPIO_Ctrl_Led_OFF(BOARD_GPIO_LED_CONFIG_GREEN);
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
* Goal: Create a program thar lissens from a gpio interrupt and blink a let accordingly
*/
int main(void){
    /* Initialize board specified hardware. */
    hardware_init();
    Hw_Timer_Init();
    //Log
    PRINTF("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\r================= Giovanni Rasera Demo: 16.31 ==================\n\r");
	GPIO_Ctrl_Init();

    /* Create a the APP main task. */
    xTaskCreate(ToggleTask, "Toggle Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL);
    xTaskCreate(SwitchTask, "Switch Task", configMINIMAL_STACK_SIZE,NULL, tskIDLE_PRIORITY+2, NULL);

    /* Start FreeRTOS scheduler. */
    vTaskStartScheduler();

    /* should never reach this point. */
    while (true);
}

