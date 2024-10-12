/*
 * spi_integration_test.h
 *
 *  Created on: Jul 30, 2024
 *      Author: root
 */

#ifndef I2C_INTEGRATION_TEST_H_
#define I2C_INTEGRATION_TEST_H_


void setup_i2c_master_integration_test (void);
void test_BMP180_Chip_ID_Read (void);
void test_BMP180_Ctrl_Measurement_Read (void);

#endif
