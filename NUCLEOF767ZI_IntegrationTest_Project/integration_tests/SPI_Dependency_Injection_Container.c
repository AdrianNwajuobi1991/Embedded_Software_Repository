/*
 * SPI_Dependency_Injection_Container.c
 *
 *  Created on: Jul 30, 2024
 *      Author: root
 */

#include "stm32f7xx.h"
#include "SPI_Dependency_Injection.h"
#include "GPIO_Dependency_Injection.h"
#include "STM32F767ZISPIDeviceLayout.h"
#include "register_bit_utils.h"

#define SPI1EN_BITPOS		12
#define TXE_BITPOS			1
#define BSY_BITPOS			7
#define RXNE_BITPOS			0
#define OVR_BITPOS			6

spi_device getSPIDeviceInstance (int deviceInstance) {
	if (deviceInstance == SPI_INSTANCE_1) {
		return (spi_device)SPI1_BASE;
	}
}

void Wait_For_TXE (spi_device device) {
	while (registerTestBitPosition (&device->SR, TXE_BITPOS) == BIT_CLEAR) {}
}

void Wait_For_Not_BSY (spi_device device) {
	while (registerTestBitPosition (&device->SR, BSY_BITPOS) == BIT_SET) {}
}

void Wait_For_RXNE (spi_device device) {
	while (registerTestBitPosition (&device->SR, RXNE_BITPOS) == BIT_CLEAR) {}
}

void Clear_OVR_Flag (spi_device device) {
	uint32_t dummy = device->DR;
	dummy = device->SR;
	dummy += -1;
}

void initialize_SPI_Device_One (void) {
	initialize_GPIO_PORTA();
	registerSetBit (&RCC->APB2ENR, SPI1EN_BITPOS);
}

void spiDeviceCleanUp (spi_device device, SPI_Config * configOptions);

