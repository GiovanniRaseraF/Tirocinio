#include <stdbool.h>
#include "gpio_pins.h"
#include "board.h"
#include "gpio_ctrl.h"
#include "gpio_imx.h"
#include "rdc_semaphore.h"
#include "debug_console_imx.h"

#define GPIO_DEBOUNCE_DELAY    (100000)


void GPIO_Ctrl_InitSwitch1Pin(){
#ifdef BOARD_GPIO_SWITCH1_CONFIG
    /* Acquire RDC semaphore before access GPIO to avoid conflict, it's
     * necessary when GPIO RDC is configured as Semaphore Required */
    RDC_SEMAPHORE_Lock(BOARD_GPIO_SWITCH1_RDC_PDAP);
    GPIO_Init(BOARD_GPIO_SWITCH1_CONFIG->base, &Switch1);
    RDC_SEMAPHORE_Unlock(BOARD_GPIO_SWITCH1_RDC_PDAP);
#endif
}

void GPIO_Ctrl_Init(){
    GPIO_Ctrl_InitSwitch1Pin();
}


uint32_t GPIO_Ctrl_GetKey(gpio_config_t *boardGpioConfig){
    return GPIO_ReadPinInput(boardGpioConfig->base, boardGpioConfig->pin);
}

void GPIO_WaitKeyPressed(gpio_config_t *boardGpioConfig, uint32_t boardGpioRdc){
    uint32_t i, j, debounce;
    /* Wait for Key Released. */
     do
     {
         debounce = 0;
         while (0 == GPIO_ReadPinInput(boardGpioConfig->base, boardGpioConfig->pin));

         for (i = 0; i < 3; i++)
         {
             /* Delay to wait key value stable. The cycle number should be changed
              * according to M4 Core clock frequncy.
              */
             for (j = 0 ; j < GPIO_DEBOUNCE_DELAY; j++)
             {
                 __NOP();
             }

             if (1 == GPIO_ReadPinInput(boardGpioConfig->base, boardGpioConfig->pin))
             {
                 debounce++;
             }
         }

         if (debounce > 2)
         {
             break;
         }
     }
     while (1);
}
#ifdef BOARD_GPIO_KEY_CONFIG
void BOARD_GPIO_KEY_HANDLER()
{


    /* When user input captured, we disable GPIO interrupt */
    NVIC_DisableIRQ(BOARD_GPIO_KEY_IRQ_NUM);

    RDC_SEMAPHORE_Lock(BOARD_GPIO_KEY_RDC_PDAP);

    /* Disable GPIO pin interrupt */
    GPIO_SetPinIntMode(BOARD_GPIO_KEY_CONFIG->base, BOARD_GPIO_KEY_CONFIG->pin, false);
    /* Clear the interrupt state */
    GPIO_ClearStatusFlag(BOARD_GPIO_KEY_CONFIG->base, BOARD_GPIO_KEY_CONFIG->pin);

    RDC_SEMAPHORE_Unlock(BOARD_GPIO_KEY_RDC_PDAP);

#ifdef xSemaphoreGiveFromISR
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    /* Unlock the task to process the event. */
    xSemaphoreGiveFromISR(xSemaphore, &xHigherPriorityTaskWoken);

    /* Perform a context switch to wake the higher priority task. */
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
#endif
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/
