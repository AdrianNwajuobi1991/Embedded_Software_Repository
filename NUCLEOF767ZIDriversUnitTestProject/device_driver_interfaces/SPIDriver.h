#ifndef _SPI_DRIVER_H
#define _SPI_DRIVER_H

#include <stdint.h>

#include "GPIODriver.h"

typedef struct SPI_TypeDef_t * spi_device;

typedef struct SPI_HalfDuplex_Config {
	uint8_t direction;
}SPI_HalfDuplex_Config;

typedef struct SPI_Config {
	uint8_t spi_device_role;
	uint8_t spi_device_mode;
	uint8_t spi_baud_rate;
	uint8_t byte_order;
	uint8_t slave_mangement_mode;
	uint8_t data_size;
	uint8_t transciever_setting;
	SPI_HalfDuplex_Config half_duplex_config;
}SPI_Config;

enum {
	SPI_INSTANCE_1
};

enum {
	SPI_MASTER, SPI_SLAVE
};

enum {
	MSB_FIRST, LSB_FIRST
};

enum {
	HARDWARE_SLAVE_MANAGEMENT, SOFTWARE_SLAVE_MANAGEMENT
};

enum {
	EIGHT_BITS, SIXTEEN_BITS
};

enum {
	FULL_DUPLEX, HALF_DUPLEX
};

enum {
	DEFAULT_PCLK_DIV16, DEFAULT_PCLK_DIV8
};

enum {
	QUARTER_LEVEL, HALF_LEVEL
};

enum {
	HD_TX_ONLY, HD_RX_ONLY
};

enum {
	SPI_MODE_ZERO, SPI_MODE_ONE, SPI_MODE_TWO, SPI_MODE_THREE
};

void configureSPIDevice (spi_device device, SPI_Config * configOptions);

void enable_spi_device (spi_device device);

void spi_manual_slave_select (gpio_device gpioPort, uint8_t slaveDeviceInstance);

void spi_manual_slave_release (gpio_device gpioPort, uint8_t slaveDeviceInstance);

void spi_transceive_packet_bytes(spi_device device, uint8_t * packetTX, uint8_t * packetRX, uint32_t length);


#endif
