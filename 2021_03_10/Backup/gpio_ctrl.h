
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
 * @brief Toggle LED on/off status
 */
void GPIO_Ctrl_ToggleLed(gpio_config_t *boardGpioConfig, uint32_t boardGpioRdc);
/*!
 * @brief Clear LED on/off status
 */
void GPIO_Ctrl_ClearLed(gpio_config_t *boardGpioConfig, uint32_t boardGpioRdc);
/*!
 * @brief Set LED on/off status
 */
void GPIO_Ctrl_SetLed(gpio_config_t *boardGpioConfig, uint32_t boardGpioRdc);
/*!
 * @brief write LED on/off status
 */
void GPIO_Ctrl_WriteLed(gpio_config_t *boardGpioConfig, uint32_t boardGpioRdc, uint32_t value);
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
/*******************************************************************************
 * EOF
 ******************************************************************************/
