/*
 * spi_integration_test.h
 *
 *  Created on: Jul 30, 2024
 *      Author: root
 */

#ifndef SPI_INTEGRATION_TEST_H_
#define SPI_INTEGRATION_TEST_H_

#define SLAVE_SELECT_PIN		PIN4

void setup_spi_master_integration_test (uint8_t spi_mode);
void test_get_ADXL345_Device_ID (void);
void test_set_ADXL345_Power_CTL_Registers (void);
void test_set_ADXL345_BW_Rate_Registers (void);
void test_read_ADXL345_Power_CTL_Registers (void);
void test_tx_only_Arduino_Slave (void);
void test_CMD_Arduino_Slave_LED_CTRL (void);

#endif /* SPI_INTEGRATION_TEST_H_ */
