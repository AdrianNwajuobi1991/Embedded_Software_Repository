/*
 * RTC_Driver_Dependency_Injection.h
 *
 *  Created on: Dec 24, 2024
 *      Author: root
 */

#ifndef RTC_DRIVER_DEPENDENCY_INJECTION_H_
#define RTC_DRIVER_DEPENDENCY_INJECTION_H_

#include "RTC_Driver.h"
#include <stdbool.h>

rtc_device getRTCDeviceInstance (void);

void Initialize_RTC_APB_Interface (void);

void RTCDeviceInstanceCleanUp (void);

void enterInitMode(rtc_device device);

bool isInitialized (rtc_device device);

void exitInitMode(rtc_device device);

void waitForRSFRDY(rtc_device device);


#endif /* RTC_DRIVER_DEPENDENCY_INJECTION_H_ */
