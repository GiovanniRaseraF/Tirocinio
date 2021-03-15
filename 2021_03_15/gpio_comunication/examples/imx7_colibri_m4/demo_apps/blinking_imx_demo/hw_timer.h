#ifndef __HW_TIMER_H__
#define __HW_TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Initialize hardware timer, must be called before Hardware_Timer_Delay().
 */
void Hw_Timer_Init(void);

/*!
 * @brief Block task for some time with hardware timer, this timer is not multi-thread
 *  safe and could only called in one task.
 *
 * @param ms milliseconds to delay
 */
void Hw_Timer_Delay(uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif /* __HW_TIMER_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/
