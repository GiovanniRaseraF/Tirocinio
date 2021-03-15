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
void GPIO_Ctrl_ToggleLed(void);

/*!
 * @brief Wait user to press key
 */
void GPIO_Ctrl_WaitKeyPressed(void);

#ifdef __cplusplus
}
#endif

#endif /* __GPIO_CTRL_H__ */
