/*
 * I2CDriver.h
 *
 *  Created on: Aug 1, 2024
 *      Author: root
 */

#ifndef I2CDRIVER_H_
#define I2CDRIVER_H_

#include <stdint.h>

typedef struct I2C_TypeDef_t * i2c_device;

typedef struct I2C_TX_RX_Config {
	uint8_t slave_address;
	int8_t device_role;
	int8_t second_transfer_direction;
	uint8_t * data_packet_write;
	uint8_t * data_packet_read;
	uint32_t packet_size_write;
	uint32_t packet_size_read;
}I2C_TX_RX_Config;

typedef struct I2C_Config {
	uint8_t dnf_filter_value;
	uint32_t timing_value;
	uint8_t use_dma_flag;
}I2C_Config;

enum {
	I2C_MASTER, I2C_SLAVE
};

enum {
	I2C_READ, NA
};

enum {
	USE_DMA_TRUE, USE_DMA_FALSE
};

enum {
	I2C_1
};

enum {
	STOP_CONDITION, REPEATED_START
};


void configureI2CDevice (i2c_device device, I2C_Config * config);

void enableI2CDevice (i2c_device device);

void I2C_transcieve_packet(i2c_device device, I2C_TX_RX_Config * i2cTranscieverSetup);

#endif /* I2CDRIVER_H_ */
