/*
 * PWRDriverTest.c
 *
 *  Created on: Nov 4, 2024
 *      Author: root
 */

#include "unity.h"
#include "PWRControlDriver.h"
#include "PWRDriverTest.h"
#include "PWRDriverTestHelper.h"

extern power_control_device powerControlDevice;

void test_PWR_OverDrive_Enable (void) {
	configurePowerControlOverDriveMode(powerControlDevice, OVR_DRV_ENABLE);
	TEST_ASSERT_EQUAL_HEX32(0x0001C000, getPWR_CR1RValue(powerControlDevice));
}

void test_PWR_VOS_Set_Scale3 (void) {
	configurePowerControlVoltageOutputScaling(powerControlDevice, SCALE_3);
	TEST_ASSERT_EQUAL_HEX32(0x00004000, getPWR_CR1RValue(powerControlDevice));
}

void test_PWR_OverDriveSwitch_Enable (void) {
	configurePowerControlOverDriveSwitchMode(powerControlDevice, OVR_DRVSW_ENABLE);
	TEST_ASSERT_EQUAL_HEX32(0x0002C000, getPWR_CR1RValue(powerControlDevice));
}

void test_PWR_Enter_Stop_Mode_Main_Regulator_ON_AND_Flash_Memory_ON (void) {

	PWR_Low_Power_Mode_Options_t lowPowerOptions;
	lowPowerOptions.stopModeOptions.voltage_regulator_setting = MAIN_REGULATOR;
	lowPowerOptions.stopModeOptions.flash_memory_settings = FLASH_MEMORY_ENABLED;
	lowPowerOptions.stopModeOptions.operation_mode = NORMAL_MODE;
	configurePowerControlLowPowerMode (powerControlDevice, STOP_MODE, false, &lowPowerOptions);
	TEST_ASSERT_EQUAL_HEX32(0x0000C000, getPWR_CR1RValue(powerControlDevice));
}

void test_PWR_Enter_Stop_Mode_Main_Regulator_ON_AND_Flash_Memory_POWER_DOWN (void) {

	PWR_Low_Power_Mode_Options_t lowPowerOptions;
	lowPowerOptions.stopModeOptions.voltage_regulator_setting = MAIN_REGULATOR;
	lowPowerOptions.stopModeOptions.flash_memory_settings = FLASH_MEMORY_DISABLED;
	lowPowerOptions.stopModeOptions.operation_mode = NORMAL_MODE;
	configurePowerControlLowPowerMode (powerControlDevice, STOP_MODE, false, &lowPowerOptions);
	TEST_ASSERT_EQUAL_HEX32(0x0000C200, getPWR_CR1RValue(powerControlDevice));
}

void test_PWR_Enter_Stop_Mode_Low_Power_Regulator_ON_AND_Flash_Memory_ON (void) {

	PWR_Low_Power_Mode_Options_t lowPowerOptions;
	lowPowerOptions.stopModeOptions.voltage_regulator_setting = LOW_POWER_REGULATOR;
	lowPowerOptions.stopModeOptions.flash_memory_settings = FLASH_MEMORY_ENABLED;
	lowPowerOptions.stopModeOptions.operation_mode = NORMAL_MODE;
	configurePowerControlLowPowerMode (powerControlDevice, STOP_MODE, false, &lowPowerOptions);
	TEST_ASSERT_EQUAL_HEX32(0x0000C001, getPWR_CR1RValue(powerControlDevice));
}

void test_PWR_Enter_Stop_Mode_Low_Power_Regulator_ON_AND_Flash_Memory_OFF (void) {

	PWR_Low_Power_Mode_Options_t lowPowerOptions;
	lowPowerOptions.stopModeOptions.voltage_regulator_setting = LOW_POWER_REGULATOR;
	lowPowerOptions.stopModeOptions.flash_memory_settings = FLASH_MEMORY_DISABLED;
	lowPowerOptions.stopModeOptions.operation_mode = NORMAL_MODE;
	configurePowerControlLowPowerMode (powerControlDevice, STOP_MODE, false, &lowPowerOptions);
	TEST_ASSERT_EQUAL_HEX32(0x0000C201, getPWR_CR1RValue(powerControlDevice));
}
