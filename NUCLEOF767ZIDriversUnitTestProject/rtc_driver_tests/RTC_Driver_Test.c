/*
 * RTC_Driver_Test.c
 *
 *  Created on: Dec 24, 2024
 *      Author: root
 */

#include "unity.h"
#include "RTC_Driver_Test.h"
#include "RTC_Driver.h"
#include "RTC_DriverTestHelper.h"


extern rtc_device rtcDevice;

void test_RTC_Device_RESET_STATE (void) {
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getRTC_ISRValue(rtcDevice));
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getRTC_CRValue(rtcDevice));
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getRTC_PRER(rtcDevice));
	TEST_ASSERT_EQUAL_HEX32(0x00002101, getRTC_DRValue(rtcDevice));
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getRTC_TRValue(rtcDevice));
}

void RTC_Initialize_Async_Sync_Prescalers_ASYNC_124_SYNC_7999 (void) {

	RTC_Initialize(rtcDevice, 124, 7999, (RTC_Date_Time_t *)0, AM, TIME_FMT_12_HR);
	TEST_ASSERT_EQUAL_HEX32(0x007C1F3F, getRTC_PRER(rtcDevice));
}

void test_RTC_Initialization_12_HR_TIME_FORMAT_AM_Set_Date_Time_TO_12_26_24_4_11_30_WDU_4 (void) {
	RTC_Date_Time_t rtcDateTime = {0};
	rtcDateTime.month = 12;
	rtcDateTime.day = 26;
	rtcDateTime.year = 24;
	rtcDateTime.dayOfWeek = 4; //Wednesday
	rtcDateTime.hours = 4;
	rtcDateTime.minutes = 11;
	rtcDateTime.seconds = 30;
	RTC_Initialize(rtcDevice, 124, 7999, &rtcDateTime, AM, TIME_FMT_12_HR);
	TEST_ASSERT_EQUAL_HEX32(0x00041130, getRTC_TRValue(rtcDevice));
	TEST_ASSERT_EQUAL_HEX32(0x00000040, getRTC_CRValue(rtcDevice));
	TEST_ASSERT_EQUAL_HEX32(0x00249226, getRTC_DRValue(rtcDevice));
}

void test_RTC_Date_Time_Readout_12_26_24_4_11_30_WDU_4 (void) {

	RTC_Date_Time_t rtcDateTime = {0};
	rtcDateTime.month = 12;
	rtcDateTime.day = 26;
	rtcDateTime.year = 24;
	rtcDateTime.dayOfWeek = 4; //Wednesday
	rtcDateTime.hours = 4;
	rtcDateTime.minutes = 11;
	rtcDateTime.seconds = 30;
	RTC_Initialize(rtcDevice, 124, 7999, &rtcDateTime, AM, TIME_FMT_12_HR);

	RTC_Date_Time_t rtcDateTimeReadOut = {0};
	RTC_ReadDateTime(rtcDevice, &rtcDateTimeReadOut);


	TEST_ASSERT_EQUAL_UINT16(4, rtcDateTimeReadOut.hours);
	TEST_ASSERT_EQUAL_UINT16(11, rtcDateTimeReadOut.minutes);
	TEST_ASSERT_EQUAL_UINT16(30, rtcDateTimeReadOut.seconds);
	TEST_ASSERT_EQUAL_UINT16(12, rtcDateTimeReadOut.month);
	TEST_ASSERT_EQUAL_UINT16(26, rtcDateTimeReadOut.day);
	TEST_ASSERT_EQUAL_UINT16(24, rtcDateTimeReadOut.year);
	TEST_ASSERT_EQUAL_UINT16(4, rtcDateTimeReadOut.dayOfWeek);
}

void test_RTC_GET_TIME_FORMAT_AS_12_HR_AND_GET_AM_FLAG (void) {
	RTC_Date_Time_t rtcDateTime = {0};
	rtcDateTime.month = 12;
	rtcDateTime.day = 26;
	rtcDateTime.year = 24;
	rtcDateTime.dayOfWeek = 4; //Wednesday
	rtcDateTime.hours = 4;
	rtcDateTime.minutes = 11;
	rtcDateTime.seconds = 30;
	RTC_Initialize(rtcDevice, 124, 7999, &rtcDateTime, AM, TIME_FMT_12_HR);

	TEST_ASSERT_EQUAL_UINT16(TIME_FMT_12_HR, RTC_GetTimeFormat(rtcDevice));
	TEST_ASSERT_EQUAL_UINT16(AM, RTC_Get_AMPM_Flag(rtcDevice));
}

