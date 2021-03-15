
/*!
**  @addtogroup pin_mux_module pin_mux module documentation
**  @{
*/

#ifndef __PIN_MUX_H__
#define __PIN_MUX_H__

/* MODULE pin_mux. */

#include "device_imx.h"

/*
** ===================================================================
**     Method      :  pin_mux_CAN (component PinSettings)
*/
/*!
**     @brief
**         CAN method sets registers according routing
**         settings. Call this method code to route desired pins into:
**         CAN1, CAN2
**         peripherals.
**     @param
**         CAN_Type* base - CAN base address 1..2
*/
/* ===================================================================*/
void configure_flexcan_pins(CAN_Type* base);

/*
** ===================================================================
**     Method      :  pin_mux_I2C (component PinSettings)
*/
/*!
**     @brief
**         I2C method sets registers according routing settings. Call
**         this method code to route desired pins into:
**         I2C1, I2C2, I2C3, I2C4
**         peripherals.
**     @param
**         I2C_Type* base - I2C base address 1..4
*/
/* ===================================================================*/
void configure_i2c_pins(I2C_Type* base);

/*
** ===================================================================
**     Method      :  pin_mux_UART (component PinSettings)
*/
/*!
**     @brief
**         UART method sets registers according routing settings. Call
**         this method code to route desired pins into:
**         UART1, UART2, UART3, UART4, UART5, UART6, UART7
**         peripherals.
**     @param
**         UART_Type* base - UART base address 1..7
*/
/* ===================================================================*/
void configure_uart_pins(UART_Type* base);

/*!
**     @brief
**         ECSPI method sets registers according routing settings. Call
**         this method code to route desired pins into:
**         ECSPI1, ECSPI2, ECSPI3, ECSPI4
**         peripherals.
**     @param
**         ECSPI_Type* base - ECSPI base address 1..4
*/
void configure_ecspi_pins(ECSPI_Type* base);


#endif /* __PIN_MUX_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/
