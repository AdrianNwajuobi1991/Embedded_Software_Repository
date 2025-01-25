/*
 * PWRControlDriver.h
 *
 *  Created on: Nov 4, 2024
 *      Author: root
 */

#ifndef PWRCONTROLDRIVER_H_
#define PWRCONTROLDRIVER_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct PWR_TypeDef_t * power_control_device;

typedef struct PWR_Stop_Mode_Options_t {
	uint8_t voltage_regulator_setting;
	uint8_t flash_memory_settings;
	uint8_t operation_mode;
}PWR_Stop_Mode_Options_t;

typedef struct PWR_Low_Power_Mode_Options_t {
	PWR_Stop_Mode_Options_t stopModeOptions;
}PWR_Low_Power_Mode_Options_t;

enum {
	MAIN_REGULATOR = 0, LOW_POWER_REGULATOR= 1
};

enum {
	FLASH_MEMORY_ENABLED = 0, FLASH_MEMORY_DISABLED = 1
};

enum {
	NORMAL_MODE = 0b00, UNDER_DRIVE_MODE = 0b11
};

enum {
	OVR_DRV_ENABLE=1, OVR_DRV_DISABLE=0
};

enum {
	SCALE_3=0b01, SCALE_2=0b10, SCALE_1=0b11
};

enum {
	OVR_DRVSW_ENABLE=1, OVR_DRVSW_DISABLE=0
};

enum {
	DBP_ENABLE = 1, DBP_DISABLE = 0
};

enum {
	SLEEP_MODE=0, STOP_MODE=1
};

void configurePowerControlBackupDomainWriteProtection (power_control_device device, uint8_t dbpFlag);

void configurePowerControlOverDriveMode (power_control_device device, uint8_t overDriveSettingFlag);

void configurePowerControlVoltageOutputScaling (power_control_device device, uint8_t vosSettingFlag);

void configurePowerControlOverDriveSwitchMode (power_control_device device, uint8_t overDriveSwitchSettingFlag);

void configurePowerControlLowPowerMode (power_control_device device, uint8_t lowPowerModeFlag,
		bool sleepOnExitFlag, PWR_Low_Power_Mode_Options_t * lowPowerOptions);


#endif /* PWRCONTROLDRIVER_H_ */
