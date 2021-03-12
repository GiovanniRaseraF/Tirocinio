/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////
#define APP_TASK_STACK_SIZE 256

/*
 * APP decided interrupt priority
 */
#define APP_MU_IRQ_PRIORITY 3


/******************************************************************************
 *
 * Function Name: ToggleTask
 * Comments: this task is used to turn toggle on/off LED.
 *
 ******************************************************************************/
static void StrEchoTask(void *pvParameters)
{
    bool key1PressCount = 0;
    bool key1PressCountOld = 0;
    bool key2PressCount = 0;
    bool key2PressCountOld = 0;
    bool sendNewData = 0;

    int result;
    struct remote_device *rdev = NULL;
    struct rpmsg_channel *app_chnl = NULL;
    char str_buffer[256] ;
    char str_copyBack[256];
    int len;
    void *rx_buf;
    void *tx_buf;
    unsigned long size;
    unsigned long src;

    /* Print the initial banner */
    PRINTF("\r\nRPMSG String Echo FreeRTOS RTOS API Demo...\r\n");

    /* RPMSG Init as REMOTE */
    PRINTF("RPMSG Init as Remote\r\n");
    result = rpmsg_rtos_init(0 /*REMOTE_CPU_ID*/, &rdev, RPMSG_MASTER, &app_chnl);
    assert(result == 0);
    PRINTF("Name service handshake is done, M4 has setup a rpmsg channel [%d ---> %d]\r\n", app_chnl->src, app_chnl->dst);


    sendNewData = 1;
    PRINTF("================== RPMSG DONE===================\n\r");

    while(true)
    {
        /* Get RPMsg rx buffer with message */
        result = rpmsg_rtos_recv_nocopy(app_chnl->rp_ept, &rx_buf, &len, &src, 0);

        /* Copy string from RPMsg rx buffer */
        assert(len < sizeof(str_buffer));
        memcpy(str_buffer, rx_buf, len);
        memcpy(str_copyBack, rx_buf, len);
        str_buffer[len] = 0; /* End string by '\0' */
		str_copyBack[len] = 0;

        //Ricevuto il messaggio Oralo rimando con una messaggio alla fine

        /* free rx buffer */
        result = rpmsg_rtos_recv_nocopy_free(app_chnl->rp_ept, rx_buf);
		
		//Lo setto per rimandarlo 
		sendNewData = 1;

        /* Switch changed*/
        if(sendNewData == 1)
        {
            sendNewData = 0;
            memset(str_buffer, 0, sizeof(str_buffer));

            PRINTF("================== key1PressCount = %d ==================\n\r", key1PressCount);
            PRINTF("================== key2PressCount = %d ==================\n\r", key2PressCount);

            /* Create message */
            len = snprintf(str_buffer, sizeof(str_buffer),"FreeRTOS: %s\n",
                    str_copyBack);

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
        }
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


/******************************************************************************
 *
 * Function Name: main
 * Comments: Hello World Example with GPIO.
 *   This example include:
 *   Configure BUTTON1 as GPIO functionality
 *     and check the button's state(pressed or released). According to the Button
 *     status, copy it to the LED
 *
 ******************************************************************************/
int main(void)
{
    /* hardware initialiize, include RDC, IOMUX, Uart debug initialize */
    hardware_init();
    PRINTF("\n\r\n\r\n\r");
    PRINTF("=======================================================\n\r");
    PRINTF("============ GPIO FreeRtos and MCC Example ============\n\r");
    PRINTF("========== Play with Led and Button and MCC ===========\n\r");
    PRINTF("=======================================================\n\r");


    /* GPIO module initialize, configure "LED" as output and button as interrupt mode. */
    GPIO_Ctrl_Init();

    /*
     * Prepare for the MU Interrupt
     *  MU must be initialized before rpmsg init is called
     */
    MU_Init(BOARD_MU_BASE_ADDR);
    NVIC_SetPriority(BOARD_MU_IRQ_NUM, APP_MU_IRQ_PRIORITY);
    NVIC_EnableIRQ(BOARD_MU_IRQ_NUM);

    /* Create a demo task. */
    xTaskCreate(StrEchoTask, "String Echo Task", APP_TASK_STACK_SIZE,
                NULL, tskIDLE_PRIORITY+1, NULL);

    /* Start FreeRTOS scheduler. */
    vTaskStartScheduler();

    /* Should never reach this point. */
    while (true);
}
/*******************************************************************************
 * EOF
 ******************************************************************************/
