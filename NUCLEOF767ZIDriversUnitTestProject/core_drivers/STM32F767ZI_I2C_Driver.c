/*
 * STM32F767ZI_I2C_Driver.c
 *
 *  Created on: Aug 1, 2024
 *      Author: root
 */
#include "I2CDriver.h"
#include "STM32F767ZI_I2CDriverDeviceLayout.h"
#include "register_bit_utils.h"
#include <stdint.h>
#include "I2C_Dependency_Injection.h"

#define SCLL_BITPOS		0
#define SCLH_BITPOS		8
#define SDADEL_BITPOS	16
#define SCLDEL_BITPOS	20
#define PRESC_BITPOS	28
#define NBYTES_BITPOS	16
#define SADD_BITPOS		0
#define AUTOEND_BITPOS	25
#define START_BITPOS	13
#define PE_BITPOS		0
#define TC_BITPOS		6
#define DNF_BITPOS		8
#define STOP_BITPOS		14
#define RD_WRN_BITPOS	10

static void setupI2CCommon (i2c_device device, I2C_TX_RX_Config * i2cTranscieverSetup);

static void setupFirstI2CTransaction (i2c_device device, I2C_TX_RX_Config * i2cTranscieverSetup);

static void setupSecondI2CTransaction (i2c_device device, I2C_TX_RX_Config * i2cTranscieverSetup);

void configureI2CDevice (i2c_device device, I2C_Config * config) {
	registerClearBit (&device->CR1, PE_BITPOS);
	registerSetValueInBitPosition (&device->CR1, config->dnf_filter_value, DNF_BITPOS);
	registerOverwriteValue (&device->TIMINGR, config->timing_value);
	if (config->use_dma_flag == USE_DMA_TRUE) {
		//Do DMA initialization then return
		return;
	}
	return;
}

void I2C_transcieve_packet(i2c_device device, I2C_TX_RX_Config * i2cTranscieverSetup) {
	uint8_t nackInTransmit;
	setupFirstI2CTransaction(device, i2cTranscieverSetup);
	/*
	 * check for NACKF flag set in the I2C_ISR register.
	 * If it is set, clear the NACKCF bit end the transaction and return.
	 */
	if (checkForAndClearNACKFlagSet(device) == NACKF_SET) {
		//send the STOP condition
		registerSetBit(&device->CR2, STOP_BITPOS);
		return;
	}
	/*
	 * perform a transmission at first to inform slave device.
	 */
	I2C_Transmit(device, i2cTranscieverSetup, &nackInTransmit);

	if (nackInTransmit == NACKF_SET){
		//send the STOP condition
		registerSetBit(&device->CR2, STOP_BITPOS);
		return;
	}
	/*
	 * wait for TC flag set in the I2C_ISR register to perform software actions
	 * of STOP or RESTART based on the second_transfer_direction flag.
	 * If it is NA, issue a STOP condition
	 */
	while (registerTestBitPosition (&device->ISR, TC_BITPOS) != BIT_SET) {}
	//send the STOP condition to prepare for repeated start
	registerSetBit(&device->CR2, STOP_BITPOS);
	if (i2cTranscieverSetup->second_transfer_direction != NA) {
		setupSecondI2CTransaction(device, i2cTranscieverSetup);
		I2C_Receive (device, i2cTranscieverSetup);
		return;
	}
	return;
}

void enableI2CDevice (i2c_device device) {
	registerSetBit (&device->CR1, PE_BITPOS);
}

static void setupI2CCommon (i2c_device device, I2C_TX_RX_Config * i2cTranscieverSetup) {
	//Slave Address setup
	registerSetValueInBitPosition (&device->CR2, i2cTranscieverSetup->slave_address, SADD_BITPOS);
}

static void setupFirstI2CTransaction (i2c_device device, I2C_TX_RX_Config * i2cTranscieverSetup) {
	//NBYTES
	registerSetValueInBitPosition (&device->CR2, i2cTranscieverSetup->packet_size_write, NBYTES_BITPOS);
	//clear AUTOEND to 0
	registerClearBit (&device->CR2, AUTOEND_BITPOS);
	setupI2CCommon(device, i2cTranscieverSetup);
	//usually a write, clear the read bit in CR2 because write is active low
	registerClearBit(&device->CR2, RD_WRN_BITPOS);
	if (i2cTranscieverSetup->device_role == I2C_MASTER) {
		//set START Bit if master mode is requested.
		registerSetBit (&device->CR2, START_BITPOS);
	}
}

static void setupSecondI2CTransaction (i2c_device device, I2C_TX_RX_Config * i2cTranscieverSetup) {
	//NBYTES
	registerSetValueInBitPosition (&device->CR2, i2cTranscieverSetup->packet_size_read, NBYTES_BITPOS);
	//set AUTOEND to 1
	registerSetBit (&device->CR2, AUTOEND_BITPOS);
	setupI2CCommon(device, i2cTranscieverSetup);
	//usually a read, set the read bit in CR2
	registerSetBit(&device->CR2, RD_WRN_BITPOS);
	if (i2cTranscieverSetup->device_role == I2C_MASTER) {
		//set START Bit if master mode is requested.
		registerSetBit (&device->CR2, START_BITPOS);
	}
}
