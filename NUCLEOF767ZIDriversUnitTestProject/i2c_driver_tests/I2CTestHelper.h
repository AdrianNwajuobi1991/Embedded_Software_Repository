/*
 * I2CTestHelper.h
 *
 *  Created on: Aug 1, 2024
 *      Author: root
 */

#ifndef I2CTESTHELPER_H_
#define I2CTESTHELPER_H_

#include <stdint.h>
#include "STM32F767ZI_I2CDriverDeviceLayout.h"
#include "I2CDriver.h"
#include "register_bit_utils.h"

uint32_t getI2CCR1Value (i2c_device i2cDevice);
uint32_t getI2CCR2Value (i2c_device i2cDevice);
uint32_t getI2CISRValue (i2c_device i2cDevice);
uint32_t getI2CICRValue (i2c_device i2cDevice);
uint32_t getI2CTIMINGRValue (i2c_device i2cDevice);



#endif /* I2CTESTHELPER_H_ */
