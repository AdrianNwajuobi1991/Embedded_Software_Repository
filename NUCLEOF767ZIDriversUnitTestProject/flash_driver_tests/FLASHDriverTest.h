/*
 * FLASHDriverTest.h
 *
 *  Created on: Aug 24, 2024
 *      Author: root
 */

#ifndef FLASHDRIVERTEST_H_
#define FLASHDRIVERTEST_H_

void test_FLASH_Driver_Default_State (void);
void test_FLASH_Driver_Unlock_FLASH_Control_Register (void);
void test_FLASH_Driver_Lock_FLASH_Control_Register (void);
void test_FLASH_Driver_Sector_2_Erase (void);
void test_FLASH_Driver_Sector_2_3_4_Erase (void);
void test_FLASH_Driver_Progamming_Paralleism (void);
void test_FLASH_Driver_FLASH_Write (void);
void test_FLASH_Driver_Unlock_FLASH_Option_Register (void);

#endif /* FLASHDRIVERTEST_H_ */
