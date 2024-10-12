/*
 * TimerDriverTestHelper.c
 *
 *  Created on: Aug 24, 2024
 *      Author: root
 */

#include "TIMERDriverTestHelper.h"
#include "STM32F767ZI_TIMERDeviceDriverLayout.h"
#include "register_bit_utils.h"

uint32_t getTimerEGRValue (timer_device device) {
	return registerGetValue(&device->EGR);
}

uint32_t getTimerCR1Value (timer_device device) {
	return registerGetValue(&device->CR1);
}

uint32_t getTimerCCERValue (timer_device device) {
	return registerGetValue(&device->CCER);
}

uint32_t getTimerDIERValue (timer_device device) {
	return registerGetValue(&device->DIER);
}

uint32_t getTimerCCMR1Value (timer_device device) {
	return registerGetValue(&device->CCMR1);
}

uint32_t getTimerCCMR2Value (timer_device device) {
	return registerGetValue(&device->CCMR2);
}

uint32_t getTimerARRValue (timer_device device) {
	return registerGetValue(&device->ARR);
}

uint32_t getTimerPSCValue (timer_device device) {
	return registerGetValue(&device->PSC);
}

uint32_t getTimerCCR1Value (timer_device device) {
	return registerGetValue(&device->CCR1);
}

uint32_t getTimerCCR2Value (timer_device device) {
	return registerGetValue(&device->CCR2);
}

uint32_t getTimerORValue (timer_device device) {
	return registerGetValue(&device->OR);
}

uint32_t getTimerSMCRValue (timer_device device) {
	return registerGetValue(&device->SMCR);
}
