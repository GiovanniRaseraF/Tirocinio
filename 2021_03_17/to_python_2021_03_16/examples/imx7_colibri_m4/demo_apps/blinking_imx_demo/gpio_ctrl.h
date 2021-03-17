#ifndef __GPIO_CTRL_H__
#define __GPIO_CTRL_H__

#include "gpio_pins.h"
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Initialize GPIO controller.
 */
void GPIO_Ctrl_Init(void);

//Led manipulation
#define LED_ON gpioPinSet
#define LED_OFF gpioPinClear
void GPIO_Ctrl_Led_Set(gpio_config_t *gpioLed_CynexoRGBLed_Color, gpio_pin_action_t pinVal);
void GPIO_Ctrl_Led_ON(gpio_config_t *);
void GPIO_Ctrl_Led_OFF(gpio_config_t *);

/*!
 * @brief Wait user to press key
 */
void GPIO_Ctrl_WaitKeyPressed(void);

#ifdef __cplusplus
}
#endif

#endif /* __GPIO_CTRL_H__ */
