/*
 * PWRControl_Dependency_Injection.h
 *
 *  Created on: Nov 4, 2024
 *      Author: root
 */

#ifndef PWRCONTROL_DEPENDENCY_INJECTION_H_
#define PWRCONTROL_DEPENDENCY_INJECTION_H_

#include "PWRControlDriver.h"

power_control_device getPowerControlDeviceInstance (void);

void PowerControlDeviceInstanceCleanUp (void);

void Initialize_Power_Control (void);

void waitForOverDriveRDY (power_control_device device);

void waitForOverDriveSwitchRDY(power_control_device device);

void waitForVOSRDY (power_control_device device);

void enterSleepMode (void);

void enterDeepSleepMode (void);

void enableSleepOnExit (void);

void waitForInterrupt (void);

void waitForEvent (void);

#endif /* PWRCONTROL_DEPENDENCY_INJECTION_H_ */
