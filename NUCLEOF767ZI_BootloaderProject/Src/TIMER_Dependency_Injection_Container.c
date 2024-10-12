/*
 * USART_Dependency_Injection_Container.c
 *
 *  Created on: Aug 19, 2024
 *      Author: root
 */
#include "stm32f7xx.h"
#include "TIMER_Dependency_Injection.h"
#include "STM32F767ZI_TIMERDeviceDriverLayout.h"
#include "register_bit_utils.h"

timer_device getTimerDeviceInstance (int instance) {
	if (instance == TIM_1) {
		return (timer_device)TIM1_BASE;
	}
	if (instance == TIM_4) {
		return (timer_device)TIM4_BASE;
	}
	if (instance == TIM_7) {
		return (timer_device)TIM7_BASE;
	}
	if (instance == TIM_8) {
		return (timer_device)TIM8_BASE;
	}
	if (instance == TIM_12) {
		return (timer_device)TIM12_BASE;
	}
}

void TimerDeviceInstanceCleanUp (timer_device device, PWM_TIMER_Config * config) {

}

