/*
 * SPI_Test_Dependency_Injection.c
 *
 *  Created on: Aug 1, 2024
 *      Author: root
 */

#include "STM32F767ZISPIDeviceLayout.h"
#include "SPIDriver.h"
#include <stdint.h>
#include "SPI_Dependency_Injection.h"

static SPI_TypeDef_t spiInstances[3];

spi_device getSPIDeviceInstance (int deviceInstance) {
	spiInstances[deviceInstance].CR1 = 0x00000000;
	spiInstances[deviceInstance].CR2 = 0x00000700;
	spiInstances[deviceInstance].SR = 0x00000002;
	return &spiInstances[deviceInstance];
}

void spiDeviceCleanUp (spi_device device, SPI_Config * configOptions) {
	device->CR1 = 0x00000000;
	device->CR2 = 0x00000700;
	device->SR = 0x00000002;
}

void Wait_For_RXNE (spi_device device) {
	return;
}

void Wait_For_TXE (spi_device device) {
	return;
}

void Wait_For_Not_BSY (spi_device device) {
	return;
}

void initialize_SPI_Device_One (void) {
	return;
}

void Clear_OVR_Flag (spi_device device) {
	return;
}
