
#include "gpio_imx.h"

/*******************************************************************************
 * Code
 ******************************************************************************/

/*******************************************************************************
 * GPIO Initialization and Configuration functions
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : GPIO_Init
 * Description   : Initializes the GPIO module according to the specified
 *                 parameters in the initConfig.
 *
 *END**************************************************************************/
void GPIO_Init(GPIO_Type* base, const gpio_init_config_t* initConfig){
    uint32_t pin;
    volatile uint32_t *icr;

    /* Clear Interrupt mask and edge-select for one particular GPIO */
    GPIO_IMR_REG(base) &= ~(1U << pin);
    GPIO_EDGE_SEL_REG(base) &= ~(1U << pin);

    /* Get pin number */
    pin = initConfig->pin;

    /* Configure GPIO pin direction */
    if (initConfig->direction == gpioDigitalOutput)
        GPIO_GDIR_REG(base) |= (1U << pin);
    else
        GPIO_GDIR_REG(base) &= ~(1U << pin);

    /* Configure GPIO pin interrupt mode */
    if(pin < 16)
        icr = &GPIO_ICR1_REG(base);
    else{
        icr = &GPIO_ICR2_REG(base);
        pin -= 16;
    }
    switch(initConfig->interruptMode){
        case(gpioIntLowLevel):
        {
            *icr &= ~(0x3<<(2*pin));
            break;
        }
        case(gpioIntHighLevel):
        {
            *icr = (*icr & (~(0x3<<(2*pin)))) | (0x1<<(2*pin));
            break;
        }
        case(gpioIntRisingEdge):
        {
            *icr = (*icr & (~(0x3<<(2*pin)))) | (0x2<<(2*pin));
            break;
        }
        case(gpioIntFallingEdge):
        {
            *icr |= (0x3<<(2*pin));
            break;
        }
        case(gpioNoIntmode):
        {
            break;
        }
    }
}

/*******************************************************************************
 * GPIO Read and Write Functions
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : GPIO_WritePinOutput
 * Description   : Sets the output level of the individual GPIO pin.
 *
 *END**************************************************************************/
void GPIO_WritePinOutput(GPIO_Type* base, uint32_t pin, gpio_pin_action_t pinVal){
    assert(pin < 32);
    if (pinVal == gpioPinSet){
        GPIO_DR_REG(base) |= (1U << pin);  /* Set pin output to high level.*/
    }
    else{
        GPIO_DR_REG(base) &= ~(1U << pin);  /* Set pin output to low level.*/
    }
}

/*******************************************************************************
 * Interrupts and flags management functions
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : GPIO_SetPinIntMode
 * Description   : Enable or Disable the specific pin interrupt.
 *
 *END**************************************************************************/
void GPIO_SetPinIntMode(GPIO_Type* base, uint32_t pin, bool enable){
    assert(pin < 32);

    if(enable)
        GPIO_IMR_REG(base) |= (1U << pin);
    else
        GPIO_IMR_REG(base) &= ~(1U << pin);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : GPIO_SetIntEdgeSelect
 * Description   : Enable or Disable the specific pin interrupt.
 *
 *END**************************************************************************/

void GPIO_SetIntEdgeSelect(GPIO_Type* base, uint32_t pin, bool enable){
    assert(pin < 32);

    if(enable)
        GPIO_EDGE_SEL_REG(base) |= (1U << pin);
    else
        GPIO_EDGE_SEL_REG(base) &= ~(1U << pin);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
