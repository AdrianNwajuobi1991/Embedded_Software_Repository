/*
 * SPIDriverTestHelper.c
 *
 *  Created on: Jul 29, 2024
 *      Author: root
 */

#include "SPIDriverTestHelper.h"
#include <stdint.h>
#include "STM32F767ZISPIDeviceLayout.h"
#include "SPIDriver.h"


uint32_t getSPIx_CR1_Value (spi_device device) {
	return device->CR1;
}
uint32_t getSPIx_CR2_Value (spi_device device) {
	return device->CR2;
}
uint32_t getSPIx_SR_Value (spi_device device) {
	return device->SR;
}

uint32_t getSPIx_DR_Value (spi_device device) {
	return device->DR;
}

