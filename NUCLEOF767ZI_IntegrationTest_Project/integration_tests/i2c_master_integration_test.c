/*
 * i2c_master_integration_test.c
 *
 *  Created on: Aug 17, 2024
 *      Author: root
 */

#include "I2C_Dependency_Injection.h"
#include "i2c_integration_test.h"
#include "gpio_integration_test.h"
#include <string.h>
#include "I2CDriver.h"

static i2c_device i2cDevice1 = (i2c_device)0;
static gpio_device gpioPortB = (gpio_device)0;


void test_BMP180_Chip_ID_Read (void) {
	I2C_TX_RX_Config i2cTranscieverSetup = {0};

	uint8_t chip_id_register [] = {0xD0};
	uint8_t result[] = {0xFF};

	i2cTranscieverSetup.slave_address = 0xEE;
	i2cTranscieverSetup.device_role = I2C_MASTER;
	i2cTranscieverSetup.second_transfer_direction = I2C_READ;
	i2cTranscieverSetup.data_packet_write = chip_id_register;
	i2cTranscieverSetup.data_packet_read = result;
	i2cTranscieverSetup.packet_size_write = 1;
	i2cTranscieverSetup.packet_size_read = 1;

	I2C_transcieve_packet(i2cDevice1, &i2cTranscieverSetup);

	if (result[0] == 0x55) {
		turn_on_BLUE_LED_PORTB();
	}
}

void test_BMP180_Ctrl_Measurement_Read (void) {
	I2C_TX_RX_Config i2cTranscieverSetup = {0};

	uint8_t ctrl_meas_register [] = {0xF4};
	uint8_t result[] = {0xFF};

	i2cTranscieverSetup.slave_address = 0xEE;
	i2cTranscieverSetup.device_role = I2C_MASTER;
	i2cTranscieverSetup.second_transfer_direction = I2C_READ;
	i2cTranscieverSetup.data_packet_write = ctrl_meas_register;
	i2cTranscieverSetup.data_packet_read = result;
	i2cTranscieverSetup.packet_size_write = 1;
	i2cTranscieverSetup.packet_size_read = 1;

	I2C_transcieve_packet(i2cDevice1, &i2cTranscieverSetup);

	if (result[0] == 0x00) {
		turn_on_GREEN_LED_PORTB();
	}
}

void setup_i2c_master_integration_test (void) {
	i2cDevice1 = getI2CDeviceInstance(I2C_1);
	gpioPortB = getGPIODeviceInstance(PORTB);
	initialize_I2C_Device_One();
	GPIOPortConfiguration gpioPortBConfig;

	memset(&gpioPortBConfig, 0, sizeof(gpioPortBConfig));

	gpioPortBConfig.gpioModeConfiguration = ALT_FUNC_MODE;
	gpioPortBConfig.gpioOutputSpeedConfiguration = HIGH_SPEED;
	gpioPortBConfig.gpioOutputTypeConfiguration = OPEN_DRAIN;
	gpioPortBConfig.gpioPUPDConfiguration = PULL_UP;
	gpioPortBConfig.gpioAFRHConfiguration = AF4; //I2C1 functions

	configureGPIODevice(gpioPortB, &gpioPortBConfig, PIN9); //SDA Pin
	configureGPIODevice(gpioPortB, &gpioPortBConfig, PIN8); //SCL Pin

	I2C_Config timingsConfig = {0};

	timingsConfig.dnf_filter_value = 0;
	timingsConfig.timing_value = 0x10D55F7C;//0x30E22E37;

	configureI2CDevice (i2cDevice1, &timingsConfig);
	enableI2CDevice (i2cDevice1);
}
