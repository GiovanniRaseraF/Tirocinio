#include <stdint.h>
#include <stdbool.h>
#include "uart_imx.h"
#include "board.h"

typedef struct _uart_state {
    const uint8_t*    txBuff;          /*!< The buffer of data being sent.*/
    uint8_t*          rxBuff;          /*!< The buffer of received data. */
    volatile uint32_t txSize;          /*!< The remaining number of bytes to be transmitted. */
    volatile uint32_t rxSize;          /*!< The remaining number of bytes to be received. */
    volatile bool     isTxBusy;        /*!< True if there is an active transmit. */
    volatile bool     isRxBusy;        /*!< True if there is an active receive. */
} uart_state_t;

const uint8_t buffStart[] = "\n\r++++++++++++++++ UART Send/Receive Interrupt Driven Example +++++++++++++++++\n\r";
const uint8_t bufferData[] = "\n\rType characters from keyboard, the board will receive and then echo them to terminal screen\n\r";

/* Uart runtime state structure */
static uart_state_t uartState;

static void UART_XFER_Config(uart_init_config_t* initConfig);
static bool UART_XFER_Write(uint8_t* txBuffer, uint32_t length);
static uint32_t UART_XFER_GetWriteStatus(void);
static bool UART_XFER_Read(uint8_t* rxBuffer, uint32_t length);
static uint32_t UART_XFER_GetReadStatus(void);

int main(void)
{
    // Setup UART init structure.
    uart_init_config_t initConfig = {
        .baudRate   = 115200u,
        .wordLength = uartWordLength8Bits,
        .stopBitNum = uartStopBitNumOne,
        .parity     = uartParityDisable,
        .direction  = uartDirectionTxRx
    };
    uint8_t rxChar, txChar;

    // Initialize board specified hardware.
    hardware_init();

    // Get current module clock frequency.
    initConfig.clockRate  = get_uart_clock_freq(BOARD_DEBUG_UART_BASEADDR);

    // Initialize the uart module with initialize structure.
    UART_XFER_Config(&initConfig);

    // Inform to start non blocking example.
    UART_XFER_Write((uint8_t*)buffStart, sizeof(buffStart));
    // Wait until transmission is finished.
    while (UART_XFER_GetWriteStatus());

    // Inform user of what to do
    UART_XFER_Write((uint8_t*)bufferData, sizeof(bufferData));
    // Wait until transmission is finished.
    while (UART_XFER_GetWriteStatus());

    while (true)
    {
        // Call received API
        UART_XFER_Read(&rxChar, 1u);

        // Wait until we receive a character
        while (UART_XFER_GetReadStatus());

        // Echo received character
        txChar = rxChar;
        UART_XFER_Write(&txChar, 1u);
    }
}

static void UART_XFER_Config(uart_init_config_t* initConfig)
{
    /* Assert */

    /* Initialize UART state structure content. */
    uartState.txBuff = 0;
    uartState.rxBuff = 0;
    uartState.txSize = 0;
    uartState.rxSize = 0;
    uartState.isTxBusy = false;
    uartState.isRxBusy = false;

    /* Initialize UART baud rate, bit count, parity, stop bit and direction. */
    UART_Init(BOARD_DEBUG_UART_BASEADDR, initConfig);
    UART_SetModemMode(BOARD_DEBUG_UART_BASEADDR, uartModemModeDte);

    UART_SetTxFifoWatermark(BOARD_DEBUG_UART_BASEADDR, 16);
    UART_SetRxFifoWatermark(BOARD_DEBUG_UART_BASEADDR, 1);

    /* Set UART Interrupt priority */
    NVIC_SetPriority(BOARD_DEBUG_UART_IRQ_NUM, 3);

    /* Call core API to enable the IRQ. */
    NVIC_EnableIRQ(BOARD_DEBUG_UART_IRQ_NUM);

    /* Finally, enable the UART module */
    UART_Enable(BOARD_DEBUG_UART_BASEADDR);
}

static bool UART_XFER_Write(uint8_t* txBuffer, uint32_t length)
{
    if ((uartState.isTxBusy) || (0 == length))
        return false;

    uartState.txBuff = txBuffer;
    uartState.txSize = length;
    uartState.isTxBusy = true;

    UART_SetIntCmd(BOARD_DEBUG_UART_BASEADDR, uartIntTxReady, true);
    return true;
}

static uint32_t UART_XFER_GetWriteStatus(void)
{
    return uartState.txSize;
}

static bool UART_XFER_Read(uint8_t* rxBuffer, uint32_t length)
{
    if ((uartState.isRxBusy) || (0 == length))
        return false;
    uartState.rxBuff = rxBuffer;
    uartState.rxSize = length;
    uartState.isRxBusy = true;

    UART_SetIntCmd(BOARD_DEBUG_UART_BASEADDR, uartIntRxReady, true);
    return true;
}

static uint32_t UART_XFER_GetReadStatus(void)
{
    return uartState.rxSize;
}

void BOARD_DEBUG_UART_HANDLER(void)
{
    /* Exit the ISR if no transfer is happening for this instance. */
    if ((!uartState.isTxBusy) && (!uartState.isRxBusy))
        return;

    if (UART_GetStatusFlag(BOARD_DEBUG_UART_BASEADDR, uartStatusRxReady))
    {
        /* Check to see if there are any more bytes to receive. */
        if (uartState.rxSize)
        {
            while (UART_GetStatusFlag(BOARD_DEBUG_UART_BASEADDR, uartStatusRxReady))
            {
                *(uartState.rxBuff) = (uint8_t)UART_Getchar(BOARD_DEBUG_UART_BASEADDR);
                uartState.rxBuff++;
                uartState.rxSize--;
                if (uartState.rxSize == 0U)
                {
                    UART_SetIntCmd(BOARD_DEBUG_UART_BASEADDR, uartIntRxReady, false);
                    
                    uartState.isRxBusy = false;
                    break;
                }
            }
        }
    }

    if (UART_GetStatusFlag(BOARD_DEBUG_UART_BASEADDR, uartStatusTxReady))
    {
        /* Check to see if there are any more bytes to send. */
        if (uartState.txSize)
        {
            while (UART_GetStatusFlag(BOARD_DEBUG_UART_BASEADDR, uartStatusTxReady))
            {
                /* Transmit data and update tx size/buff */
                UART_Putchar(BOARD_DEBUG_UART_BASEADDR, *(uartState.txBuff));
                uartState.txBuff++;
                uartState.txSize--;
                if (uartState.txSize == 0U)
                {
                    /* Transmit complete */
                    /* Disable the transmitter ready interrupt */
                    UART_SetIntCmd(BOARD_DEBUG_UART_BASEADDR, uartIntTxReady, false);

                    /* Update the information of the module driver state */
                    uartState.isTxBusy = false;
                    break;
                }
            }
        }
    }
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
