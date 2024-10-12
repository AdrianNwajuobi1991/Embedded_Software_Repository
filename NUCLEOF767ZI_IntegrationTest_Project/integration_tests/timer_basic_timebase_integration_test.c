/*
 *  Created on: Oct 4, 2024
 *      Author: root
 */

#include "timer_basic_timebase_integration_test.h"
#include "TIMER_Driver.h"
#include "TIMER_Dependency_Injection.h"
#include <string.h>
#include "GPIODriver.h"
#include "GPIO_Dependency_Injection.h"
#include "GPIO_Device_Common.h"
#include "gpio_integration_test.h"
#include "register_bit_utils.h"
#include "stm32f7xx.h"


static timer_device timer5;
static timer_device timer3;
static volatile uint32_t timerBaseCounterValue = 0;


void polled_timer_test (void) {

	checkAndClearTimerUpdateInterruptFlag (timer5);
	timerBaseCounterValue += 1;
	toggle_all_LEDs_PORTB();
}

void setup_basic_timebase_integration_test_interrupt_enabled (void) {
	Initialize_TIMER3 ();
	timer3 = getTimerDeviceInstance(TIM_3);
	disableTimer (timer3);
	configureTimeBaseGeneration (timer3, 15999, 999);
	configureTimerDMAInterrupts(timer3, UIE);
	NVIC_SetPriorityGrouping(0);
	NVIC_SetPriority (TIM3_IRQn, 1);
	NVIC_EnableIRQ (TIM3_IRQn);
	enableTimer (timer3);
}

void setup_basic_timebase_integration_test_no_interrupts (void) {
	Initialize_TIMER5 ();
	timer5 = getTimerDeviceInstance(TIM_5);
	disableTimer (timer5);
	configureTimeBaseGeneration (timer5, 15, 199999);
	enableTimer (timer5);
}

void TIM3_IRQHandler (void) {
	toggle_all_LEDs_PORTB();
	if (registerTestBitPosition (&timer3->SR, 0) == BIT_SET) {
		registerClearBit (&timer3->SR, 0);
		timerBaseCounterValue += 1;
	}
}
