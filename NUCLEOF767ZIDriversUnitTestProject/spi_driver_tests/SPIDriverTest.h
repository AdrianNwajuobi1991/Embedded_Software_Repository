/*
 * SPIDriverTest.h
 *
 *  Created on: Jul 29, 2024
 *      Author: root
 */

#ifndef SPIDRIVERTEST_H_
#define SPIDRIVERTEST_H_

void test_GetSPIInstance_Instance_Has_Default_Values (void);
void test_Config_Master_Mode_One_FullDuplex_2MHZ_MSBFirst_SSM_Disabled_8BitData_FiFoThreshold_Quarter (void);
void test_Config_Slave_Mode_One_FullDuplex_2MHZ_MSBFirst_SSM_Disabled_8BitData_FiFoThreshold_Quarter (void);
void test_Config_Slave_Mode_Three_FullDuplex_2MHZ_MSBFirst_SSM_Disabled_8BitData_FiFoThreshold_Quarter (void);

#endif /* SPIDRIVERTEST_H_ */
