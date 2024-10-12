/*
 * I2C_Test_Dependency_Injection.c
 *
 *  Created on: Aug 4, 2024
 *      Author: root
 */

#include "STM32F767ZI_I2CDriverDeviceLayout.h"
#include "I2CDriver.h"
#include "I2C_Dependency_Injection.h"
#include "register_bit_utils.h"
#include <stdint.h>


static I2C_TypeDef_t I2C_Devices[1];

i2c_device getI2CDeviceInstance (int i2cDeviceInstance) {
	I2C_Devices[i2cDeviceInstance].CR1 = 0x00000000;
	I2C_Devices[i2cDeviceInstance].CR2 = 0x00000000;
	I2C_Devices[i2cDeviceInstance].ISR = 0x00000001;
	I2C_Devices[i2cDeviceInstance].ICR = 0x00000000;
	I2C_Devices[i2cDeviceInstance].TIMINGR = 0x00000000;
	return &I2C_Devices[i2cDeviceInstance];
}

void I2C_Transmit (i2c_device device, I2C_TX_RX_Config * i2cTranscieverSetup, uint8_t * nackInTransmitFlag) {
	return;
}

void I2C_Receive (i2c_device device, I2C_TX_RX_Config * i2cTranscieverSetup) {
	return;
}

int8_t checkForAndClearNACKFlagSet (i2c_device device) {
	return NACKF_CLEAR;
}

void I2CDeveiceCleanUp(i2c_device device, I2C_Config * I2CConfig) {
	registerOverwriteValue (&device->CR1, 0x00000000);
	registerOverwriteValue (&device->CR2, 0x00000000);
	registerOverwriteValue (&device->ISR, 0x00000001);
	registerOverwriteValue (&device->ICR, 0x00000000);
	registerOverwriteValue (&device->TIMINGR, 0x00000000);
}
