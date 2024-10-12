/*
 * I2C_Dependency_Injection.h
 *
 *  Created on: Aug 1, 2024
 *      Author: root
 */

#ifndef I2C_DEPENDENCY_INJECTION_H_
#define I2C_DEPENDENCY_INJECTION_H_

#include "I2CDriver.h"
#include "GPIODriver.h"
#include "GPIO_Dependency_Injection.h"
#include "GPIO_Device_Common.h"

#define NACKF_SET	1
#define NACKF_CLEAR	0

i2c_device getI2CDeviceInstance(int i2cDeviceInstance);

int8_t checkForAndClearNACKFlagSet (i2c_device device);

void initialize_I2C_Device_One (void);

void I2C_Transmit (i2c_device device, I2C_TX_RX_Config * i2cTranscieverSetup, uint8_t * nackFlag);

void I2C_Receive (i2c_device device, I2C_TX_RX_Config * i2cTranscieverSetup);

void I2CDeveiceCleanUp(i2c_device device, I2C_Config * I2CConfig);



#endif /* I2C_DEPENDENCY_INJECTION_H_ */
