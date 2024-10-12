/*
 * I2CTestHelper.c
 *
 *  Created on: Aug 1, 2024
 *      Author: root
 */
#include "I2CTestHelper.h"

uint32_t getI2CCR1Value (i2c_device i2cDevice) {
	return registerGetValue(&i2cDevice->CR1);
}

uint32_t getI2CCR2Value (i2c_device i2cDevice) {
	return registerGetValue(&i2cDevice->CR2);
}

uint32_t getI2CISRValue (i2c_device i2cDevice) {
	return registerGetValue(&i2cDevice->ISR);
}

uint32_t getI2CICRValue (i2c_device i2cDevice) {
	return registerGetValue(&i2cDevice->ICR);
}

uint32_t getI2CTIMINGRValue (i2c_device i2cDevice) {
	return registerGetValue(&i2cDevice->TIMINGR);
}
