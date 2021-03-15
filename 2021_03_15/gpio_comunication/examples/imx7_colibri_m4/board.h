#if !defined(__BOARD_H__)
#define __BOARD_H__

#include "pin_mux.h"
#include "rdc.h"
#include "rdc_defs_imx7d.h"
#include "ccm_imx7d.h"
#include "clock_freq.h"


/* The board name */
#define BOARD_NAME                            "IMX7_COLIBRI_M4"
#define BOARD_DOMAIN_ID                       (1)

/* ADC information for this board */
#define BOARD_ADC_RDC_PDAP                    rdcPdapAdc1
#define BOARD_ADC_CCM_CCGR                    ccmCcgrGateAdc
#define BOARD_ADC_BASEADDR                    ADC1
#define BOARD_ADC_IRQ_NUM                     ADC1_IRQn
#define BOARD_ADC_HANDLER                     ADC1_Handler
#define BOARD_ADC_INPUT_CHANNEL               (3)

/* WDOG information for this board */
#define BOARD_WDOG_RDC_PDAP                   rdcPdapWdog3
#define BOARD_WDOG_CCM_ROOT                   ccmRootWdog
#define BOARD_WDOG_CCM_CCGR                   ccmCcgrGateWdog3
#define BOARD_WDOG_BASEADDR                   WDOG3
#define BOARD_WDOG_IRQ_NUM                    WDOG3_IRQn
#define BOARD_WDOG_HANDLER                    WDOG3_Handler

/* SEMA4 information for this board */
#define BOARD_SEMA4_RDC_PDAP                  rdcPdapSemaphoreHs
#define BOARD_SEMA4_CCM_CCGR                  ccmCcgrGateSemaHs
#define BOARD_SEMA4_BASEADDR                  SEMA4
#define BOARD_SEMA4_IRQ_NUM                   SEMA4_HS_M4_IRQn
#define BOARD_SEMA4_HANDLER                   SEMA4_HS_M4_Handler

/* GPT instance A information for this board */
#define BOARD_GPTA_RDC_PDAP                   rdcPdapGpt3
#define BOARD_GPTA_CCM_ROOT                   ccmRootGpt3
#define BOARD_GPTA_CCM_CCGR                   ccmCcgrGateGpt3
#define BOARD_GPTA_BASEADDR                   GPT3
#define BOARD_GPTA_IRQ_NUM                    GPT3_IRQn
#define BOARD_GPTA_HANDLER                    GPT3_Handler
/* GPT instance B information for this board */
#define BOARD_GPTB_RDC_PDAP                   rdcPdapGpt4
#define BOARD_GPTB_CCM_ROOT                   ccmRootGpt4
#define BOARD_GPTB_CCM_CCGR                   ccmCcgrGateGpt4
#define BOARD_GPTB_BASEADDR                   GPT4
#define BOARD_GPTB_IRQ_NUM                    GPT4_IRQn
#define BOARD_GPTB_HANDLER                    GPT4_Handler

/* GPIO information for this board */
#define BOARD_GPIO_KEY_CCM_CCGR               ccmCcgrGateGpio2

////Cynexo board Specific////
//RGB led
#define BOARD_GPIO_LED_RDC_PDAP                 rdcPdapGpio2
#define BOARD_GPIO_LED_CONFIG                   (&gpioLed_CynexoRGBLed_Green)
#define BOARD_GPIO_LED_CONFIG_GREEN             (&gpioLed_CynexoRGBLed_Green)
#define BOARD_GPIO_LED_CONFIG_RED               (&gpioLed_CynexoRGBLed_Red)
#define BOARD_GPIO_LED_CONFIG_BLUE              (&gpioLed_CynexoRGBLed_Blue)

//Interupt handler
#define BOARD_GPIO_KEY_RDC_PDAP               rdcPdapGpio2
#define BOARD_GPIO_KEY_CONFIG                 (&gpioKeyFunc_CynexoFrontButton)
#define BOARD_GPIO_KEY_IRQ_NUM                GPIO5_INT15_0_IRQn
#define BOARD_GPIO_KEY_HANDLER                GPIO5_INT15_0_Handler

/* Switch CynexoFrontButton*/
#define BOARD_GPIO_SWITCH_CynexoFrontButton_RDC_PDAP                rdcPdapGpio2
#define BOARD_GPIO_SWITCH_CynexoFrontButton_CONFIG                  (&gpioSwitch_CynexoFrontButton)

/* LED CynexoRGBLed_Green*/
#define BOARD_GPIO_LED_CynexoRGBLed_Green_RDC_PDAP                  rdcPdapGpio2
#define BOARD_GPIO_LED_CynexoRGBLed_Green_CONFIG                    (&gpioLed_CynexoRGBLed_Green)
/* LED CynexoRGBLed_Red*/
#define BOARD_GPIO_LED_CynexoRGBLed_Red_RDC_PDAP                    rdcPdapGpio2
#define BOARD_GPIO_LED_CynexoRGBLed_Red_CONFIG                      (&gpioLed_CynexoRGBLed_Red)
/* LED CynexoRGBLed_Blue*/
#define BOARD_GPIO_LED_CynexoRGBLed_Blue_RDC_PDAP                   rdcPdapGpio2
#define BOARD_GPIO_LED_CynexoRGBLed_Blue_CONFIG                     (&gpioLed_CynexoRGBLed_Blue)
/////////////////////

/* Colibri SPI is ECSPI3 */
#define BOARD_ECSPI_RDC_PDAP                  rdcPdapEcspi3
#define BOARD_ECSPI_CCM_ROOT                  ccmRootEcspi3
#define BOARD_ECSPI_CCM_CCGR                  ccmCcgrGateEcspi3
#define BOARD_ECSPI_BASEADDR                  ECSPI3
#define BOARD_ECSPI_CHANNEL                   ecspiSelectChannel0
#define BOARD_ECSPI_IRQ_NUM                   eCSPI3_IRQn
#define BOARD_ECSPI_HANDLER                   eCSPI3_Handler

/* Debug UART information for this board */
#define BOARD_DEBUG_UART_RDC_PDAP             rdcPdapUart2
#define BOARD_DEBUG_UART_CCM_ROOT             ccmRootUart2
#define BOARD_DEBUG_UART_CCM_CCGR             ccmCcgrGateUart2
#define BOARD_DEBUG_UART_BASEADDR             UART2
#define BOARD_DEBUG_UART_IRQ_NUM              UART2_IRQn
#define BOARD_DEBUG_UART_HANDLER              UART2_Handler

/* MU information for this board*/
#define BOARD_MU_HANDLER                      MU_M4_Handler
#define BOARD_MU_IRQ_NUM                      MU_M4_IRQn
#define BOARD_MU_BASE_ADDR                    MUB
#define BOARD_MU_CCM_CCGR                     ccmCcgrGateMu
#define BOARD_MU_RDC_PDAP                     rdcPdapMuB

/* I2C information for this board */
#define BOARD_I2C_RDC_PDAP                    rdcPdapI2c4
#define BOARD_I2C_CCM_ROOT                    ccmRootI2c4
#define BOARD_I2C_CCM_CCGR                    ccmCcgrGateI2c4
#define BOARD_I2C_BASEADDR                    I2C4
#define BOARD_I2C_IRQ_NUM                     I2C4_IRQn
#define BOARD_I2C_HANDLER                     I2C4_Handler
#define BOARD_I2C_FXAS21002_ADDR              (0x20)
#define BOARD_I2C_FXOS8700_ADDR               (0x1E)

/* FlexCAN information for this board */
#define BOARD_FLEXCAN_RDC_PDAP                rdcPdapFlexCan1
#define BOARD_FLEXCAN_CCM_ROOT                ccmRootCan1
#define BOARD_FLEXCAN_CCM_CCGR                ccmCcgrGateCan1
#define BOARD_FLEXCAN_BASEADDR                CAN1
#define BOARD_FLEXCAN_IRQ_NUM                 FLEXCAN1_IRQn
#define BOARD_FLEXCAN_HANDLER                 FLEXCAN1_Handler

/* GPC information for this board*/
#define BOARD_GPC_BASEADDR                    GPC

/* SIM_WAKEUP CG information*/
#define BOARD_SIM_WAKEUP_CCGR                 ccmCcgrGateSimWakeup

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

void hardware_init(void);
void dbg_uart_init(void);
/* Function to initialize clock base on board configuration. */
void BOARD_ClockInit(void);
void BOARD_RdcInit(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __BOARD_H__ */
