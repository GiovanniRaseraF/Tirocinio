#ifndef __GPIO_PINS_H__
#define __GPIO_PINS_H__

#include "device_imx.h"
#include "gpio_imx.h"


/*! @brief i.MX GPIO initialize structure. */
typedef struct _gpio_config
{
    const char        *name;
    __IO  uint32_t    *muxReg;
    uint32_t           muxConfig;
    __IO  uint32_t    *padReg;
    uint32_t           padConfig;
    GPIO_Type         *base;
    uint32_t           pin;
} gpio_config_t;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*! @brief GPIO pin configuration */
extern gpio_config_t gpioLed;
extern gpio_config_t gpioKeyFunc1;
extern gpio_config_t gpioKeyFunc2;
extern gpio_config_t gpioKeyFunc3;

extern gpio_config_t gpioSwitch1;
extern gpio_config_t gpioLed1;
extern gpio_config_t gpioSwitch2;
extern gpio_config_t gpioLed2;
extern gpio_config_t gpioSwitch3;

extern gpio_init_config_t Switch1;
extern gpio_init_config_t Led1;
extern gpio_init_config_t Switch2;
extern gpio_init_config_t Led2;
extern gpio_init_config_t Switch3;

/*! @brief Configure specific GPIO pin */
void configure_gpio_pin(gpio_config_t *config);

#endif /* __GPIO_PINS_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/
