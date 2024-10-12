/*
 * SPI_Dependency_Injection.h
 *
 *  Created on: Jul 30, 2024
 *      Author: root
 */

#ifndef SPI_DEPENDENCY_INJECTION_H_
#define SPI_DEPENDENCY_INJECTION_H_

#include "SPIDriver.h"

spi_device getSPIDeviceInstance (int deviceInstance);

void Wait_For_TXE (spi_device device);

void Wait_For_Not_BSY (spi_device device);

void Wait_For_RXNE (spi_device device);

void Clear_OVR_Flag (spi_device device);

void initialize_SPI_Device_One (void);

void spiDeviceCleanUp (spi_device device, SPI_Config * configOptions);



#endif /* SPI_DEPENDENCY_INJECTION_H_ */
