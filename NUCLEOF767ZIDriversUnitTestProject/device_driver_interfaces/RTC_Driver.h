/*
 * RTC_Driver.h
 *
 *  Created on: Dec 24, 2024
 *      Author: root
 */

#ifndef RTC_DRIVER_H_
#define RTC_DRIVER_H_

#include <stdint.h>

typedef struct RTC_Date_Time_t {

	uint16_t month;
	uint16_t day;
	uint16_t year;
	uint16_t dayOfWeek;
	uint16_t hours;
	uint16_t minutes;
	uint16_t seconds;
}RTC_Date_Time_t;

enum {
	TIME_FMT_24_HR=0, TIME_FMT_12_HR=1
};
enum {
	AM=0, PM=1
};

typedef struct RTC_TypeDef_t * rtc_device;

void RTC_Initialize (rtc_device device, uint8_t preDivAValue, uint16_t preDivSValue,
		RTC_Date_Time_t * rtcDateTime, uint8_t amPmFlag, uint8_t timeFormatFlag);

void RTC_ReadDateTime (rtc_device device, RTC_Date_Time_t * rtcDateTimeReadOut);

void RTC_WriteProtectUnlock (rtc_device device);

uint8_t RTC_GetTimeFormat (rtc_device device);

uint8_t RTC_Get_AMPM_Flag (rtc_device device);

#endif /* RTC_DRIVER_H_ */
