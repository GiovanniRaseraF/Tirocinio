#ifndef __GPIO_PINS_H__
#define __GPIO_PINS_H__

#include "device_imx.h"
#include "gpio_imx.h"

/*! @brief i.MX GPIO initialize structure. */
typedef struct _gpio_config{
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

/*! @brief GPIO pin Cynexo Board Specific */
//Buttons
extern gpio_config_t gpioKeyFunc_CynexoFrontButton;
extern gpio_config_t gpioSwitch_CynexoFrontButton;
extern gpio_init_config_t Switch_CynexoFrontButton;

//Led RGB
extern gpio_config_t gpioLed_CynexoRGBLed_Green;
extern gpio_init_config_t Led_CynexoRGBLed_Green;
extern gpio_config_t gpioLed_CynexoRGBLed_Red;
extern gpio_init_config_t Led_CynexoRGBLed_Red;
extern gpio_config_t gpioLed_CynexoRGBLed_Blue;
extern gpio_init_config_t Led_CynexoRGBLed_Blue;

/*! @brief Configure specific GPIO pin */
void configure_gpio_pin(gpio_config_t *config);

#endif /* __GPIO_PINS_H__ */
