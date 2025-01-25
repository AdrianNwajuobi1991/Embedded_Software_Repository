/*
 * STM32F767ZI_PWRControl_Driver.c
 *
 *  Created on: Nov 4, 2024
 *      Author: root
 */

#include "PWRControlDriver.h"
#include "register_bit_utils.h"
#include "STM32F767ZI_PWRControlDeviceDriverLayout.h"
#include "PWRControl_Dependency_Injection.h"

void configurePowerControlOverDriveMode(power_control_device device, uint8_t overDriveSettingFlag) {
	registerClearValueInBitPosition (&device->CR1, 0x1, 16);
	registerSetValueInBitPosition (&device->CR1, overDriveSettingFlag, 16);
	if (overDriveSettingFlag == OVR_DRV_ENABLE) {
		waitForOverDriveRDY(device);
	}
}

void configurePowerControlBackupDomainWriteProtection (power_control_device device, uint8_t dbpFlag) {
	registerClearValueInBitPosition (&device->CR1, 0x1, 8);
	registerSetValueInBitPosition (&device->CR1, dbpFlag, 8);
}

void configurePowerControlVoltageOutputScaling (power_control_device device, uint8_t vosSettingFlag) {
	registerClearValueInBitPosition (&device->CR1, 0x3, 14);
	registerSetValueInBitPosition (&device->CR1, vosSettingFlag, 14);
	if (vosSettingFlag != SCALE_3) {
		waitForVOSRDY(device);
	}
}

void configurePowerControlOverDriveSwitchMode(power_control_device device, uint8_t overDriveSwitchSettingFlag) {
	registerClearValueInBitPosition (&device->CR1, 0x1, 17);
	registerSetValueInBitPosition (&device->CR1, overDriveSwitchSettingFlag, 17);
	if (overDriveSwitchSettingFlag == OVR_DRV_ENABLE) {
		waitForOverDriveSwitchRDY(device);
	}
}

void configurePowerControlLowPowerMode (power_control_device device, uint8_t lowPowerModeFlag,
		bool sleepOnExitFlag, PWR_Low_Power_Mode_Options_t * lowPowerOptions) {
	if (sleepOnExitFlag == true) {
		enableSleepOnExit();
	}
	if (lowPowerModeFlag == SLEEP_MODE) {
		enterSleepMode();
	}
	if (lowPowerModeFlag == STOP_MODE) {
		enterDeepSleepMode();
		registerClearBit (&device->CR1, 1); // clear PDDS bit
		if (lowPowerOptions->stopModeOptions.operation_mode == NORMAL_MODE) {
			//clear LPDS bit
			registerSetValueInBitPosition (&device->CR1, lowPowerOptions->stopModeOptions.voltage_regulator_setting, 0);
			//clear FPDS bit
			registerSetValueInBitPosition (&device->CR1, lowPowerOptions->stopModeOptions.flash_memory_settings, 9);
		}
	}
}
