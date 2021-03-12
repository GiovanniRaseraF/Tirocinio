#include "FreeRTOS.h"
#include "task.h"
#include "board.h"
#include "debug_console_imx.h"
#include "gpio_ctrl.h"
#include "hw_timer.h"
#define BLINKING_INTERVAL_MIN    (100)

static volatile uint32_t blinkingInterval = BLINKING_INTERVAL_MIN;

/******************************************************************************
*
* Function Name: ToggleTask
* Comments: this task is used to turn toggle on/off LED.
*
******************************************************************************/
void ToggleTask(void *pvParameters){
    while (true){
        GPIO_Ctrl_ToggleLed();
        /* Use Hardware timer to get accurate delay */
        Hw_Timer_Delay(blinkingInterval);
    }
}

/******************************************************************************
*
* Function Name: SwitchTask
* Comments: this task is used to change blinking frequency.
*
******************************************************************************/
void SwitchTask(void *pvParameters){
    while (true){
        PRINTF("\n\r====== Blinking interval %dms ======\n\r", blinkingInterval);
        GPIO_Ctrl_WaitKeyPressed();
        blinkingInterval += 100;
        if (blinkingInterval > 1000)
            blinkingInterval = BLINKING_INTERVAL_MIN;
        /* Delay for 1 second to avoid glitch */
        vTaskDelay(configTICK_RATE_HZ);
    }
}

/******************************************************************************
*
* Function Name: main
* Comments: main function, toggle LED and switch the blinking frequency by key.
*
******************************************************************************/
int main(void){
    /* Initialize board specified hardware. */
    hardware_init();

    Hw_Timer_Init();
    GPIO_Ctrl_Init();

    PRINTF("\n\r================= Blinking Demo ==================\n\r");

    /* Create a the APP main task. */
    xTaskCreate(ToggleTask, "Toggle Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL);

    /* Interrupt Button */
    xTaskCreate(SwitchTask, "Switch Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+2, NULL);

    /* Start FreeRTOS scheduler. */
    vTaskStartScheduler();
    while (true);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
