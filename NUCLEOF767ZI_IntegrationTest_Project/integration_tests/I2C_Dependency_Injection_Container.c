/*
 * I2C_Dependency_Injection_Container.c
 *
 *  Created on: Aug 16, 2024
 *      Author: root
 */

#include "stm32f7xx.h"
#include "I2C_Dependency_Injection.h"
#include "GPIO_Dependency_Injection.h"
#include "STM32F767ZI_I2CDriverDeviceLayout.h"
#include "register_bit_utils.h"


#define NACKF_BITPOS	4
#define NACKCF_BITPOS	4
#define I2C1EN_BITPOS	21
#define STOP_BITPOS		14
#define TXIS_BITPOS		1
#define RXNE_BITPOS		2

i2c_device getI2CDeviceInstance(int i2cDeviceInstance) {
	if (i2cDeviceInstance == I2C_1) {
		return (i2c_device)I2C1;
	}
}

void initialize_I2C_Device_One (void) {
	//enable corresponding GPIO instance
	initialize_GPIO_PORTB();
	//enable clock access
	registerSetBit(&RCC->APB1ENR, I2C1EN_BITPOS);
}

int8_t checkForAndClearNACKFlagSet (i2c_device device) {
	if (registerTestBitPosition (&device->ISR, NACKF_BITPOS) == BIT_SET) {
		//clear the flag by setting NACKCF in ICR
		registerSetBit (&device->ICR, NACKCF_BITPOS);
		//send the STOP condition
		registerSetBit(&device->CR2, STOP_BITPOS);
		return NACKF_SET;
	}
	return NACKF_CLEAR;
}

void I2C_Receive (i2c_device device, I2C_TX_RX_Config * i2cTranscieverSetup) {
	int count = 0;
	while (count < i2cTranscieverSetup->packet_size_read) {
		//test the RXNE bit of I2C_ISR.
		if (registerTestBitPosition (&device->ISR, RXNE_BITPOS) == BIT_SET) {
			//if it is set, read the data and increment the count.
			i2cTranscieverSetup->data_packet_read[count] = device->RXDR;
			count++;
		}
	}
}

void I2C_Transmit (i2c_device device, I2C_TX_RX_Config * i2cTranscieverSetup, uint8_t * nackFlag) {
	int count = 0;
	while (count < i2cTranscieverSetup->packet_size_write) {
		//test the TXIS bit of I2C_ISR.
		if (registerTestBitPosition (&device->ISR, TXIS_BITPOS) == BIT_SET) {
			//if it is set, write the data and increment the count.
			device->TXDR = i2cTranscieverSetup->data_packet_write[count];
			count++;
		}
		//check for NACK.
		if (checkForAndClearNACKFlagSet(device) == NACKF_SET) {
			//if NACK is received break out of the loop.
			*nackFlag = NACKF_SET;
			break;
		}
	}
}

void I2CDeveiceCleanUp(i2c_device device, I2C_Config * I2CConfig) {

}
