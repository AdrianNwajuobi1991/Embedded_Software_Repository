/*
 * STM32F767ZISPIDriver.c
 *
 *  Created on: Jul 29, 2024
 *      Author: root
 */
#include "SPIDriver.h"
#include "STM32F767ZISPIDeviceLayout.h"
#include "SPI_Dependency_Injection.h"
#include "register_bit_utils.h"


#define MSTR_BITPOS		2
#define CPOL_BITPOS		1
#define	CPHA_BITPOS		0
#define BR_BITPOS		3
#define LSB_MSB_BITPOS	7
#define SSI_BITPOS		8
#define SSM_BITPOS		9
#define SSOE_BITPOS		2
#define BIDIMODE_BITPOS	15
#define BIDIOE_BITPOS	14
#define DS_BITPOS		8
#define FRXTH_BITPOS	12
#define SPE_BITPOS		6
#define CPOL_0			0
#define CPHA_0			0
#define CPOL_1			1
#define CPHA_1			1

static void configure_spi_clock_polarity_and_phase (spi_device device, SPI_Config * configOptions);

static void configure_spi_byte_order (spi_device device, SPI_Config * configOptions);

static void configure_spi_slave_management (spi_device device, SPI_Config * configOptions);

static void configure_spi_transciever (spi_device device, SPI_Config * configOptions);

static void configure_spi_data_size_and_fifo_threshold (spi_device device, SPI_Config * configOptions);


void configureSPIDevice (spi_device device, SPI_Config * configOptions) {
	configure_spi_clock_polarity_and_phase (device, configOptions);
	configure_spi_slave_management(device, configOptions);
	configure_spi_data_size_and_fifo_threshold(device, configOptions);
	configure_spi_transciever(device, configOptions);
	configure_spi_byte_order(device, configOptions);
	if (configOptions->spi_device_role == SPI_MASTER) {
		registerSetBit (&device->CR1, MSTR_BITPOS);
	}
}

void spi_manual_slave_select (gpio_device gpioPort, uint8_t slaveDeviceInstance) {
	resetGPIOPinNumberBSRR(gpioPort, slaveDeviceInstance);
}

void spi_manual_slave_release (gpio_device gpioPort, uint8_t slaveDeviceInstance) {
	setGPIOPinNumberBSRR(gpioPort, slaveDeviceInstance);
}

void spi_transceive_packet_bytes(spi_device device, uint8_t * packetTX, uint8_t * packetRX, uint32_t length) {
	int count = 0;
	Wait_For_Not_BSY(device);
	while (count < length) {
		Wait_For_TXE(device);
		*(uint8_t *)(&(device->DR)) = packetTX[count];
		Wait_For_RXNE(device);
		packetRX[count] = (uint8_t)device->DR;
		count++;
	}
	Wait_For_Not_BSY(device);
	Clear_OVR_Flag(device);
}

void enable_spi_device (spi_device device) {
	device->CR1 |= (1 << SPE_BITPOS);
}

static void configure_spi_byte_order (spi_device device, SPI_Config * configOptions) {
	if (configOptions->byte_order == LSB_FIRST) {
		registerSetBit(&device->CR1, LSB_MSB_BITPOS);
	}
	if (configOptions->byte_order == MSB_FIRST) {
		registerClearBit(&device->CR1, LSB_MSB_BITPOS);
	}
}

static void configure_spi_slave_management (spi_device device, SPI_Config * configOptions) {
	//set SSM
	if (configOptions->slave_mangement_mode == HARDWARE_SLAVE_MANAGEMENT) {
		// set SSM bit to Zero to indicate non-software management of slave
		registerClearBit(&device->CR1, SSM_BITPOS);
		if (configOptions->spi_device_role == SPI_MASTER) {
			// set SSOE bit to high to enable pulling low or high the NSS line
			registerSetBit(&device->CR2, SSOE_BITPOS);
		}
	}
	if (configOptions->slave_mangement_mode == SOFTWARE_SLAVE_MANAGEMENT) {
		// set SSM bit to 1 to indicate software slave management is active
		registerSetBit(&device->CR1, SSM_BITPOS);
		if (configOptions->spi_device_role == SPI_MASTER) {
			registerSetBit(&device->CR1, SSI_BITPOS);
		}
	}
}

static void configure_spi_transciever (spi_device device, SPI_Config * configOptions) {
	//set baud rate
	if (configOptions->spi_device_role == SPI_MASTER) {
		if (configOptions->spi_baud_rate == DEFAULT_PCLK_DIV16) {
			registerSetValueInBitPosition (&device->CR1, 3, BR_BITPOS);
		}else if (configOptions->spi_baud_rate == DEFAULT_PCLK_DIV8) {
			registerSetValueInBitPosition (&device->CR1, 2, BR_BITPOS);
		}
	}
	if (configOptions->transciever_setting == FULL_DUPLEX) {
		registerClearBit(&device->CR1, BIDIMODE_BITPOS);
	}
	if (configOptions->transciever_setting == HALF_DUPLEX) {
		registerSetBit(&device->CR1, BIDIMODE_BITPOS);
		//check half_duplex_config
		if (configOptions->half_duplex_config.direction == HD_TX_ONLY) {
			registerSetBit(&device->CR1, BIDIOE_BITPOS);
		}
		if (configOptions->half_duplex_config.direction == HD_RX_ONLY) {
			registerClearBit(&device->CR1, BIDIOE_BITPOS);
		}
	}
}

static void configure_spi_data_size_and_fifo_threshold (spi_device device, SPI_Config * configOptions) {
	if (configOptions->data_size == EIGHT_BITS) {
		//set DS to 8 bits
		registerSetValueInBitPosition (&device->CR2, 7, DS_BITPOS);
		//set FRXTH to 8-bit depth
		registerSetBit(&device->CR2, FRXTH_BITPOS);
	}
	if (configOptions->data_size == SIXTEEN_BITS) {
		//set DS to 16 bits
		registerSetValueInBitPosition (&device->CR2, 15, DS_BITPOS);
		//set FRXTH to 16-bit depth
		registerClearBit(&device->CR2, FRXTH_BITPOS);
	}
}

static void configure_spi_clock_polarity_and_phase (spi_device device, SPI_Config * configOptions) {
	if (configOptions->spi_device_mode == SPI_MODE_ZERO) {
		registerClearBit(&device->CR1, CPHA_BITPOS);
		registerClearBit(&device->CR1, CPOL_BITPOS);
	}
	if (configOptions->spi_device_mode == SPI_MODE_ONE) {
		registerSetBit(&device->CR1, CPHA_BITPOS);
		registerClearBit(&device->CR1, CPOL_BITPOS);
	}
	if (configOptions->spi_device_mode == SPI_MODE_TWO) {
		registerClearBit(&device->CR1, CPHA_BITPOS);
		registerSetBit(&device->CR1, CPOL_BITPOS);
	}
	if (configOptions->spi_device_mode == SPI_MODE_THREE) {
		registerSetBit(&device->CR1, CPHA_BITPOS);
		registerSetBit(&device->CR1, CPOL_BITPOS);
	}
}
