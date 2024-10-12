/*
 * I2CDriverTest.c
 *
 *  Created on: Aug 1, 2024
 *      Author: root
 */
#include "I2CDriver.h"

#include "unity.h"
#include "I2CTestHelper.h"
#include "I2CDriverTest.h"
#include "I2C_Dependency_Injection.h"


extern i2c_device i2cDevice1;


void test_I2C_RegisterValuesAreCorrectDefaults (void) {
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getI2CCR1Value(i2cDevice1));
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getI2CCR2Value(i2cDevice1));
	TEST_ASSERT_EQUAL_HEX32(0x00000001, getI2CISRValue(i2cDevice1));
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getI2CICRValue(i2cDevice1));
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getI2CTIMINGRValue(i2cDevice1));
}

void test_I2C_StandardMode_FI2CCLK16MHZ_100KHZ_SPEED_AFON_DNF_15X (void) {
	I2C_Config timingsConfig = {0};

	timingsConfig.dnf_filter_value = 1;
	timingsConfig.timing_value = 0x20630712;

	configureI2CDevice(i2cDevice1, &timingsConfig);
	TEST_ASSERT_EQUAL_HEX32(0x00000100, getI2CCR1Value(i2cDevice1));
	TEST_ASSERT_EQUAL_HEX32(0x20630712, getI2CTIMINGRValue(i2cDevice1));
}

void test_I2C_Master_TransmitLessthan255_Bytes_NO_RELOAD_NO_REPEATED_START (void) {

	I2C_TX_RX_Config i2cTranscieverSetup = {0};

	uint8_t data_packet [] = {12, 23, 44, 67, 99, 89, 65, 34};

	i2cTranscieverSetup.slave_address = 0x50;
	i2cTranscieverSetup.device_role = I2C_MASTER;
	i2cTranscieverSetup.second_transfer_direction = NA;
	i2cTranscieverSetup.data_packet_write = data_packet;
	i2cTranscieverSetup.data_packet_read = (uint8_t *)0;
	i2cTranscieverSetup.packet_size_write = sizeof(data_packet);
	i2cTranscieverSetup.packet_size_read = NA;

	I2C_transcieve_packet(i2cDevice1, &i2cTranscieverSetup);

	TEST_ASSERT_EQUAL_HEX32(0x00082050, getI2CCR2Value(i2cDevice1));
}

void test_I2C_EnableDevice (void) {
	enableI2CDevice(i2cDevice1);
	TEST_ASSERT_EQUAL_HEX32(0x00000001, getI2CCR1Value(i2cDevice1));
}


