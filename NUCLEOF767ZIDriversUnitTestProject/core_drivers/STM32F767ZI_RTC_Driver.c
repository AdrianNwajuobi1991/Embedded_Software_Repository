/*
 * STM32F767ZI_RTC_Driver.c
 *
 *  Created on: Dec 26, 2024
 *      Author: root
 */

#include "RTC_Driver.h"
#include "register_bit_utils.h"
#include "STM32F767ZI_RTC_DriverDeviceLayout.h"
#include "RTC_Driver_Dependency_Injection.h"
#include <stdbool.h>

static void set_RTC_Time_Register_12_HR_FMT (rtc_device device, RTC_Date_Time_t * rtcDateTime, uint8_t amPmFlag);
static void set_RTC_Date_Register_12_HR_FMT (rtc_device device, RTC_Date_Time_t * rtcDateTime);

void RTC_Initialize (rtc_device device, uint8_t preDivAValue, uint16_t preDivSValue,
		RTC_Date_Time_t * rtcDateTime, uint8_t amPmFlag, uint8_t timeFormatFlag) {
	if (isInitialized (device) == false) {
		enterInitMode(device);
		registerClearValueInBitPosition (&device->PRER, 0x7F, 16);
		registerClearValueInBitPosition (&device->PRER, 0xFFFF, 0);
		registerSetValueInBitPosition (&device->PRER, preDivAValue, 16);
		registerSetValueInBitPosition (&device->PRER, preDivSValue, 0);
		if (rtcDateTime != 0) {
			if (timeFormatFlag == TIME_FMT_12_HR) {
				set_RTC_Time_Register_12_HR_FMT (device, rtcDateTime, amPmFlag);
				set_RTC_Date_Register_12_HR_FMT (device, rtcDateTime);
				registerSetBit(&device->CR, 6);
			}
		}
		exitInitMode(device);
	}
}

void RTC_WriteProtectUnlock (rtc_device device) {
	device->WPR = 0xCA;
	device->WPR = 0x53;
}

uint8_t RTC_GetTimeFormat (rtc_device device) {
	return (uint8_t)(registerGetMaskBits (&device->CR, 0x1 << 6) >> 6);
}

uint8_t RTC_Get_AMPM_Flag (rtc_device device) {
	return (uint8_t)(registerGetMaskBits (&device->TR, 0x1 << 22) >> 22);
}

void RTC_ReadDateTime (rtc_device device, RTC_Date_Time_t * rtcDateTimeReadOut) {
	waitForRSFRDY(device);
	uint32_t rtc_tr_value = device->TR;
	uint32_t rtc_dr_value = device->DR;

	rtcDateTimeReadOut->hours = 10*((rtc_tr_value & (0x3 << 20)) >> 20) + ((rtc_tr_value & (0xF << 16)) >> 16);
	rtcDateTimeReadOut->minutes = 10*((rtc_tr_value & (0x7 << 12)) >> 12) + ((rtc_tr_value & (0xF << 8)) >> 8);
	rtcDateTimeReadOut->seconds = 10*((rtc_tr_value & (0x7 << 4)) >> 4) + ((rtc_tr_value & (0xF << 0)) >> 0);

	rtcDateTimeReadOut->month = 10*((rtc_dr_value & (0x1 << 12)) >> 12) + ((rtc_dr_value & (0xF << 8)) >> 8);
	rtcDateTimeReadOut->day = 10*((rtc_dr_value & (0x3 << 4)) >> 4) + ((rtc_dr_value & (0xF << 0)) >> 0);
	rtcDateTimeReadOut->year = 10*((rtc_dr_value & (0xF << 20)) >> 20) + ((rtc_dr_value & (0xF << 16)) >> 16);
	rtcDateTimeReadOut->dayOfWeek = ((rtc_dr_value & (0xF << 13)) >> 13);
}

static void set_RTC_Time_Register_12_HR_FMT (rtc_device device, RTC_Date_Time_t * rtcDateTime, uint8_t amPmFlag) {
	uint32_t rtc_tr_value = 0;
	registerSetValueInBitPosition (&rtc_tr_value, amPmFlag, 22);
	registerSetValueInBitPosition (&rtc_tr_value, rtcDateTime->hours/10, 20);
	registerSetValueInBitPosition (&rtc_tr_value, rtcDateTime->hours%10, 16);
	registerSetValueInBitPosition (&rtc_tr_value, rtcDateTime->minutes/10, 12);
	registerSetValueInBitPosition (&rtc_tr_value, rtcDateTime->minutes%10, 8);
	registerSetValueInBitPosition (&rtc_tr_value, rtcDateTime->seconds/10, 4);
	registerSetValueInBitPosition (&rtc_tr_value, rtcDateTime->seconds%10, 0);
	device->TR = rtc_tr_value;
}

static void set_RTC_Date_Register_12_HR_FMT (rtc_device device, RTC_Date_Time_t * rtcDateTime) {
	uint32_t rtc_dr_value = 0;
	registerSetValueInBitPosition (&rtc_dr_value, rtcDateTime->year/10, 20);
	registerSetValueInBitPosition (&rtc_dr_value, rtcDateTime->year%10, 16);
	registerSetValueInBitPosition (&rtc_dr_value, rtcDateTime->dayOfWeek, 13);
	registerSetValueInBitPosition (&rtc_dr_value, rtcDateTime->month/10, 12);
	registerSetValueInBitPosition (&rtc_dr_value, rtcDateTime->month%10, 8);
	registerSetValueInBitPosition (&rtc_dr_value, rtcDateTime->day/10, 4);
	registerSetValueInBitPosition (&rtc_dr_value, rtcDateTime->day%10, 0);
	device->DR = rtc_dr_value;
}
