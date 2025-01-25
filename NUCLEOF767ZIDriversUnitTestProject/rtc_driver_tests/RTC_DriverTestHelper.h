/*
 * RTC_DriverTestHelper.h
 *
 *  Created on: Dec 25, 2024
 *      Author: root
 */

#ifndef RTC_DRIVERTESTHELPER_H_
#define RTC_DRIVERTESTHELPER_H_

#include "RTC_Driver.h"
#include <stdint.h>

uint32_t getRTC_ISRValue(rtc_device device);
uint32_t getRTC_CRValue(rtc_device device);
uint32_t getRTC_PRER(rtc_device device);
uint32_t getRTC_DRValue(rtc_device device);
uint32_t getRTC_TRValue(rtc_device device);

#endif /* RTC_DRIVERTESTHELPER_H_ */
