/*
 * TIMER_Dependency_Injection.h
 *
 *  Created on: Aug 24, 2024
 *      Author: root
 */

#ifndef TIMER_DEPENDENCY_INJECTION_H_
#define TIMER_DEPENDENCY_INJECTION_H_

#include "STM32F767ZI_TIMERDeviceDriverLayout.h"
#include "TIMER_Driver.h"

enum {
	TIM_1, TIM_3, TIM_8, TIM_12, TIM_7, TIM_4, TIM_5, TIM_2
};

timer_device getTimerDeviceInstance (int instance);
void Initialize_TIMER4 (void);
void Initialize_TIMER7 (void);
void Initialize_TIMER5 (void);
void Initialize_TIMER2 (void);
void Initialize_TIMER12 (void);
void Initialize_TIMER3 (void);
void TimerDeviceInstanceCleanUp (timer_device device, PWM_TIMER_Config * config);


#endif /* TIMER_DEPENDENCY_INJECTION_H_ */
