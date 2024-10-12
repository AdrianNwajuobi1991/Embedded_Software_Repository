/*
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
	if (instance == TIM_5) {
		return (timer_device)TIM5_BASE;
	}
	if (instance == TIM_3) {
		return (timer_device)TIM3_BASE;
	}
	if (instance == TIM_2) {
		return (timer_device)TIM2_BASE;
	}
}

void Initialize_TIMER4 (void) {
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
}

void Initialize_TIMER7 (void) {
	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
}

void Initialize_TIMER12 (void) {
	RCC->APB1ENR |= RCC_APB1ENR_TIM12EN;
}

void Initialize_TIMER5 (void) {
	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
}

void Initialize_TIMER2 (void) {
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
}

void Initialize_TIMER3 (void) {
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
}

void TimerDeviceInstanceCleanUp (timer_device device, PWM_TIMER_Config * config) {

}

