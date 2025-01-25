/*
 * FLASHDriverTest.c
 *
 *  Created on: Aug 24, 2024
 *      Author: root
 */
#include "unity.h"
#include "FLASH_Driver.h"
#include "FLASHDriverTest.h"
#include "FLASHDriverTestHelper.h"
#include <stdint.h>

extern flash_device flashDevice;


void test_FLASH_Driver_Default_State (void) {
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getFlashACRRValue(flashDevice));
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getFlashKEYRValue(flashDevice));
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getFlashOPTKEYRRValue(flashDevice));
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getFlashSRRValue(flashDevice));
	TEST_ASSERT_EQUAL_HEX32(0x80000000, getFlashCRRValue(flashDevice));
	TEST_ASSERT_EQUAL_HEX32(0xFFFFAAFD, getFlashOPTCRRValue(flashDevice));
	TEST_ASSERT_EQUAL_HEX32(0x00400080, getFlashOPTCR1RValue(flashDevice));
}

void test_FLASH_Driver_Unlock_FLASH_Control_Register (void) {
	unlockFlashControlRegister (flashDevice);
	TEST_ASSERT_EQUAL_HEX32(0xCDEF89AB, getFlashKEYRValue(flashDevice));
}

void test_FLASH_Driver_Unlock_FLASH_Option_Register (void) {
	unlockFlashOptionRegister (flashDevice);
	TEST_ASSERT_EQUAL_HEX32(0x4C5D6E7F, getFlashOPTKEYRRValue(flashDevice));
}

void test_FLASH_Driver_Lock_FLASH_Control_Register (void) {
	lockFlashControlRegister (flashDevice);
	TEST_ASSERT_EQUAL_HEX32(0x80000000, getFlashCRRValue(flashDevice));
}

void test_FLASH_Driver_Sector_2_Erase (void) {
	flashSectorErase(flashDevice, 2);
	TEST_ASSERT_EQUAL_HEX32(0x80010012, getFlashCRRValue(flashDevice));
}

void test_FLASH_Driver_Sector_2_3_4_Erase (void) {
	flashSectorErase(flashDevice, 2);
	TEST_ASSERT_EQUAL_HEX32(0x80010012, getFlashCRRValue(flashDevice));
	flashSectorErase(flashDevice, 3);
	TEST_ASSERT_EQUAL_HEX32(0x8001001A, getFlashCRRValue(flashDevice));
	flashSectorErase(flashDevice, 4);
	TEST_ASSERT_EQUAL_HEX32(0x80010022, getFlashCRRValue(flashDevice));
}

void test_FLASH_Driver_Progamming_Paralleism (void) {
	setFlashParallelism(flashDevice, X32);
	TEST_ASSERT_EQUAL_HEX32(0x80000200, getFlashCRRValue(flashDevice));
}

void test_FLASH_Driver_FLASH_Write (void) {
	flashWriteData(flashDevice, (void *)0, 200, (uint8_t *)0);
	TEST_ASSERT_EQUAL_HEX32(0x80000001, getFlashCRRValue(flashDevice));
}

void test_FLASH_Driver_LATENCY_7WS_ART_ENABLE (void) {
	configureFlashLatencyAndARTSetup(flashDevice, LATENCY_7WS, ART_ENABLE);
	TEST_ASSERT_EQUAL_HEX32(0x00000207, getFlashACRRValue(flashDevice));
}

