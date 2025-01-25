/*
 * RTC_DriverTestHelper.c
 *
 *  Created on: Dec 25, 2024
 *      Author: root
 */

#include "RTC_DriverTestHelper.h"
#include "STM32F767ZI_RTC_DriverDeviceLayout.h"

uint32_t getRTC_ISRValue(rtc_device device) {
	return device->ISR;
}
uint32_t getRTC_CRValue(rtc_device device) {
	return device->CR;
}
uint32_t getRTC_PRER(rtc_device device) {
	return device->PRER;
}
uint32_t getRTC_DRValue(rtc_device device) {
	return device->DR;
}
uint32_t getRTC_TRValue(rtc_device device) {
	return device->TR;
}

