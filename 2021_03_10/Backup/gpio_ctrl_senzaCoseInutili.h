
#ifndef __GPIO_CTRL_H__
#define __GPIO_CTRL_H__

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Initialize GPIO controller.
 */
void GPIO_Ctrl_Init(void);

/*!
 * @brief Get Key on/off status
 */
uint32_t GPIO_Ctrl_GetKey(gpio_config_t *boardGpioConfig);

/*!
 * @brief Get Key on/off status
 */
void GPIO_WaitKeyPressed(gpio_config_t *boardGpioConfig, uint32_t boardGpioRdc);

#ifdef __cplusplus
}
#endif

#endif /* __GPIO_CTRL_H__ */

