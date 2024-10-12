/*
 * USARTDriverTest.c
 *
 *  Created on: May 12, 2024
 *      Author: root
 */
#include "SPIDriver.h"

#include "unity.h"
#include "SPIDriverTest.h"
#include "SPIDriverTestHelper.h"

#include "SPI_Dependency_Injection.h"

extern spi_device spiDevice;

void test_GetSPIInstance_Instance_Has_Default_Values (void) {
	TEST_ASSERT_EQUAL_UINT32(0x00000000, getSPIx_CR1_Value(spiDevice));
	TEST_ASSERT_EQUAL_UINT32(0x00000700, getSPIx_CR2_Value(spiDevice));
	TEST_ASSERT_EQUAL_UINT32(0x00000002, getSPIx_SR_Value(spiDevice));
}

void test_Config_Slave_Mode_One_FullDuplex_2MHZ_MSBFirst_SSM_Disabled_8BitData_FiFoThreshold_Quarter (void) {
	SPI_HalfDuplex_Config halfDuplexConfig = {0};
	SPI_Config config;
	config.spi_device_role = SPI_SLAVE;
	config.spi_device_mode = SPI_MODE_ONE;
	config.spi_baud_rate = DEFAULT_PCLK_DIV8;
	config.byte_order = MSB_FIRST;
	config.slave_mangement_mode = HARDWARE_SLAVE_MANAGEMENT;
	config.data_size = EIGHT_BITS;
	config.transciever_setting = FULL_DUPLEX;
	config.half_duplex_config = halfDuplexConfig;
	configureSPIDevice (spiDevice, &config);
	TEST_ASSERT_EQUAL_UINT32(0x00000001, getSPIx_CR1_Value(spiDevice));
	TEST_ASSERT_EQUAL_UINT32(0x00001700, getSPIx_CR2_Value(spiDevice));
}

void test_Config_Slave_Mode_Three_FullDuplex_2MHZ_MSBFirst_SSM_Disabled_8BitData_FiFoThreshold_Quarter (void) {
	SPI_HalfDuplex_Config halfDuplexConfig = {0};
	SPI_Config config;
	config.spi_device_role = SPI_SLAVE;
	config.spi_device_mode = SPI_MODE_THREE;
	config.spi_baud_rate = DEFAULT_PCLK_DIV8;
	config.byte_order = MSB_FIRST;
	config.slave_mangement_mode = HARDWARE_SLAVE_MANAGEMENT;
	config.data_size = EIGHT_BITS;
	config.transciever_setting = FULL_DUPLEX;
	config.half_duplex_config = halfDuplexConfig;
	configureSPIDevice (spiDevice, &config);
	TEST_ASSERT_EQUAL_UINT32(0x00000003, getSPIx_CR1_Value(spiDevice));
	TEST_ASSERT_EQUAL_UINT32(0x00001700, getSPIx_CR2_Value(spiDevice));
}

void test_Config_Master_Mode_One_FullDuplex_2MHZ_MSBFirst_SSM_Disabled_8BitData_FiFoThreshold_Quarter (void) {
	SPI_HalfDuplex_Config halfDuplexConfig = {0};
	SPI_Config config;
	config.spi_device_role = SPI_MASTER;
	config.spi_device_mode = SPI_MODE_ONE;
	config.spi_baud_rate = DEFAULT_PCLK_DIV8;
	config.byte_order = MSB_FIRST;
	config.slave_mangement_mode = HARDWARE_SLAVE_MANAGEMENT;
	config.data_size = EIGHT_BITS;
	config.transciever_setting = FULL_DUPLEX;
	config.half_duplex_config = halfDuplexConfig;
	configureSPIDevice (spiDevice, &config);
	TEST_ASSERT_EQUAL_UINT32(0x00000015, getSPIx_CR1_Value(spiDevice));
	TEST_ASSERT_EQUAL_UINT32(0x00001704, getSPIx_CR2_Value(spiDevice));
}


