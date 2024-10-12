/*
 * SPIDriverTestHelper.h
 *
 *  Created on: Jul 29, 2024
 *      Author: root
 */

#ifndef SPIDRIVERTESTHELPER_H_
#define SPIDRIVERTESTHELPER_H_

#include <stdint.h>
#include "SPIDriver.h"

uint32_t getSPIx_CR1_Value (spi_device device);
uint32_t getSPIx_CR2_Value (spi_device device);
uint32_t getSPIx_SR_Value (spi_device device);
uint32_t getSPIx_DR_Value (spi_device device);

#endif /* SPIDRIVERTESTHELPER_H_ */
