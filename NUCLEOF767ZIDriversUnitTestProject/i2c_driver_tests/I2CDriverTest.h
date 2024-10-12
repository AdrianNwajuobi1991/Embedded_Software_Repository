/*
 * I2CDriverTest.h
 *
 *  Created on: Aug 1, 2024
 *      Author: root
 */

#ifndef I2CDRIVERTEST_H_
#define I2CDRIVERTEST_H_

void test_I2C_RegisterValuesAreCorrectDefaults (void);
void test_I2C_StandardMode_FI2CCLK16MHZ_100KHZ_SPEED_AFON_DNF_15X (void);
void test_I2C_EnableDevice (void);
void test_I2C_Master_ReceiveLessthan255_Bytes_NO_RELOAD_NO_REPEATED_START (void);
void test_I2C_Master_TransmitLessthan255_Bytes_NO_RELOAD_NO_REPEATED_START (void);

#endif /* I2CDRIVERTEST_H_ */
