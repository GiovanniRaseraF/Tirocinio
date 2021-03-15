
/****************************************************************************
*
* Comments:
*   This file contains the functions which write and read the SPI memories
*   using the ECSPI driver in interrupt mode.
*
****************************************************************************/

#include "FreeRTOS.h"
#include "semphr.h"
#include "board.h"
#include "gpt.h"
#include "hw_timer.h"

static SemaphoreHandle_t xSemaphore;

void Hw_Timer_Init(void)
{
    gpt_init_config_t config = {
        .freeRun    = false,
        .waitEnable = true,
        .stopEnable = true,
        .dozeEnable = true,
        .dbgEnable  = false,
        .enableMode = true
    };

    /* Initialize GPT module */
    GPT_Init(BOARD_GPTA_BASEADDR, &config);

    /* Set GPT clock source to 24M OSC */
    GPT_SetClockSource(BOARD_GPTA_BASEADDR, gptClockSourceOsc);

    /* Set GPT interrupt priority 3 */
    NVIC_SetPriority(BOARD_GPTA_IRQ_NUM, 3);

    /* Enable NVIC interrupt */
    NVIC_EnableIRQ(BOARD_GPTA_IRQ_NUM);

    xSemaphore = xSemaphoreCreateBinary();
}

void Hw_Timer_Delay(uint32_t ms)
{
    uint64_t counter = 24000ULL * ms; /* First get the counter needed by delay time */
    uint32_t high;
    uint32_t div24m, div;

    /* Get the value that exceed maximum register counter */
    high = (uint32_t)(counter >> 32);

    /* high could not exceed 24000, so that predivider is enough */
    div24m = high / 4096; /* We need PRESCALER24M only if high exceed PRESCALER maximum value */
    div = high / (div24m + 1); /* Get PRESCALER value */

    /* Now set prescaler */
    GPT_SetOscPrescaler(BOARD_GPTA_BASEADDR, div24m);
    GPT_SetPrescaler(BOARD_GPTA_BASEADDR, div);

    /* Set GPT compare value */
    GPT_SetOutputCompareValue(BOARD_GPTA_BASEADDR, gptOutputCompareChannel1,
                              (uint32_t)(counter / (div24m + 1) / (div + 1)));

    /* Enable GPT Output Compare1 interrupt */
    GPT_SetIntCmd(BOARD_GPTA_BASEADDR, gptStatusFlagOutputCompare1, true);

    /* GPT start */
    GPT_Enable(BOARD_GPTA_BASEADDR);

    /* Wait until GPT event happens. */
    xSemaphoreTake(xSemaphore, portMAX_DELAY);
}

void BOARD_GPTA_HANDLER(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    /* When GPT time-out, we disable GPT to make sure this is a one-shot event. */
    GPT_Disable(BOARD_GPTA_BASEADDR);
    GPT_SetIntCmd(BOARD_GPTA_BASEADDR, gptStatusFlagOutputCompare1, false);
    GPT_ClearStatusFlag(BOARD_GPTA_BASEADDR, gptStatusFlagOutputCompare1);

    /* Unlock the task to process the event. */
    xSemaphoreGiveFromISR(xSemaphore, &xHigherPriorityTaskWoken);

    /* Perform a context switch to wake the higher priority task. */
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
