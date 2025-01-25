/*
 * PWRControl_Dependency_Injection.c
 *
 *  Created on: Nov 4, 2024
 *      Author: root
 */

#include "PWRControl_Dependency_Injection.h"
#include "register_bit_utils.h"
#include "STM32F767ZI_PWRControlDeviceDriverLayout.h"
#include "PWRControlDriver.h"

static PWR_TypeDef_t powerControlDevice;

power_control_device getPowerControlDeviceInstance (void) {
	power_control_device device = &powerControlDevice;
	powerControlDevice.CR1 = 0x0000C000;
	powerControlDevice.CSR1 = 0x00000000;
	powerControlDevice.CR2 = 0x00000000;
	powerControlDevice.CSR2 = 0x00000000;
	return device;
}

void PowerControlDeviceInstanceCleanUp (void) {
	powerControlDevice.CR1 = 0x0000C000;
	powerControlDevice.CSR1 = 0x00000000;
	powerControlDevice.CR2 = 0x00000000;
	powerControlDevice.CSR2 = 0x00000000;
}

void Initialize_Power_Control (void) {

}

void waitForVOSRDY (power_control_device device) {

}

void waitForOverDriveRDY (power_control_device device) {

}

void waitForOverDriveSwitchRDY(power_control_device device) {

}

void enterSleepMode (void) {

}

void enterDeepSleepMode (void) {

}

void enableSleepOnExit (void) {

}

void waitForInterrupt (void) {

}

void waitForEvent (void) {

}
