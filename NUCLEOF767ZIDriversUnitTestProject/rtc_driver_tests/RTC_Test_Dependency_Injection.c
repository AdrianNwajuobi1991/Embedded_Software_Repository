/*
 * RTC_Test_Dependency_Injection.c
 *
 *  Created on: Dec 24, 2024
 *      Author: root
 */

#include "RTC_Driver_Dependency_Injection.h"
#include "STM32F767ZI_RTC_DriverDeviceLayout.h"
#include <stdbool.h>

static RTC_TypeDef_t rtcDevice;

rtc_device getRTCDeviceInstance (void) {
	rtc_device device = &rtcDevice;
	device->ISR = 0;
	device->CR = 0;
	device->PRER = 0;
	device->DR = 0x00002101;
	device->TR = 0x00000000;
	return device;
}

void RTCDeviceInstanceCleanUp (void) {
	rtcDevice.ISR = 0;
	rtcDevice.CR = 0;
	rtcDevice.PRER = 0;
	rtcDevice.DR = 0x00002101;
	rtcDevice.TR = 0x00000000;
}

bool isInitialized (rtc_device device) {
	return false;
}

void enterInitMode(rtc_device device) {

}

void exitInitMode(rtc_device device) {

}

void waitForRSFRDY(rtc_device device) {

}
