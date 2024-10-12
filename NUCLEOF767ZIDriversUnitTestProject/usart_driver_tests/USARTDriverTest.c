/*
 * USARTDriverTest.c
 *
 *  Created on: Aug 18, 2024
 *      Author: root
 */

#include "unity.h"
#include "USARTDriverTest.h"
#include "USARTDriverTestHelper.h"
#include <stdbool.h>

extern usart_device usartDevice2;


void test_USART_Instance_Has_Default_Values (void) {
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getUSARTDeviceBRRValue(usartDevice2));
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getUSARTDeviceCR1Value(usartDevice2));
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getUSARTDeviceCR2Value(usartDevice2));
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getUSARTDeviceCR3Value(usartDevice2));
	TEST_ASSERT_EQUAL_HEX32(0x020000C0, getUSARTDeviceISRValue(usartDevice2));
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getUSARTDeviceICRValue(usartDevice2));
}

void test_USART_Configure_115200_baud_8DataBits_No_Parity_Bit_1StopBit_16MHZ_Clock_16X_Oversampling_No_DMA_Error_Interrupt (void) {
	USART_Config usartConfig = {0};

	usartConfig.baud_rate = 115200;
	usartConfig.clock_source_speed = 16000000;
	usartConfig.oversampling_mode = OVERSAMPLE_16X;
	usartConfig.use_tx_interrupt = false;
	usartConfig.use_rx_interrupt = false;
	usartConfig.use_error_interrupts = true;

	configureUSARTDevice(usartDevice2, &usartConfig);

	TEST_ASSERT_EQUAL_HEX32(0x00000000, getUSARTDeviceCR1Value(usartDevice2));
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getUSARTDeviceCR2Value(usartDevice2));
	TEST_ASSERT_EQUAL_HEX32(0x00000001, getUSARTDeviceCR3Value(usartDevice2));
	TEST_ASSERT_EQUAL_HEX32(0x0000008B, getUSARTDeviceBRRValue(usartDevice2));
}

void test_USART_Configure_115200_baud_8DataBits_No_Parity_Bit_1StopBit_16MHZ_Clock_16X_Oversampling_No_DMA_RX_Interrupt (void) {
	USART_Config usartConfig = {0};

	usartConfig.baud_rate = 115200;
	usartConfig.clock_source_speed = 16000000;
	usartConfig.oversampling_mode = OVERSAMPLE_16X;
	usartConfig.use_tx_interrupt = false;
	usartConfig.use_rx_interrupt = true;

	configureUSARTDevice(usartDevice2, &usartConfig);

	TEST_ASSERT_EQUAL_HEX32(0x00000020, getUSARTDeviceCR1Value(usartDevice2));
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getUSARTDeviceCR2Value(usartDevice2));
	TEST_ASSERT_EQUAL_HEX32(0x0000008B, getUSARTDeviceBRRValue(usartDevice2));
}

void test_USART_Configure_115200_baud_8DataBits_No_Parity_Bit_1StopBit_16MHZ_Clock_16X_Oversampling_No_DMA_TX_Interrupt (void) {
	USART_Config usartConfig = {0};

	usartConfig.baud_rate = 115200;
	usartConfig.clock_source_speed = 16000000;
	usartConfig.oversampling_mode = OVERSAMPLE_16X;
	usartConfig.use_tx_interrupt = true;
	usartConfig.use_rx_interrupt = false;

	configureUSARTDevice(usartDevice2, &usartConfig);

	TEST_ASSERT_EQUAL_HEX32(0x00000080, getUSARTDeviceCR1Value(usartDevice2));
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getUSARTDeviceCR2Value(usartDevice2));
	TEST_ASSERT_EQUAL_HEX32(0x0000008B, getUSARTDeviceBRRValue(usartDevice2));
}

void test_USART_Configure_115200_baud_8DataBits_No_Parity_Bit_1StopBit_16MHZ_Clock_16X_Oversampling_No_DMA_No_Interupts (void) {

	USART_Config usartConfig = {0};

	usartConfig.baud_rate = 115200;
	usartConfig.clock_source_speed = 16000000;
	usartConfig.oversampling_mode = OVERSAMPLE_16X;
	usartConfig.use_tx_interrupt = false;
	usartConfig.use_rx_interrupt = false;

	configureUSARTDevice(usartDevice2, &usartConfig);

	TEST_ASSERT_EQUAL_HEX32(0x00000000, getUSARTDeviceCR1Value(usartDevice2));
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getUSARTDeviceCR2Value(usartDevice2));
	TEST_ASSERT_EQUAL_HEX32(0x0000008B, getUSARTDeviceBRRValue(usartDevice2));
}

void test_USART_Configure_115200_baud_8DataBits_No_Parity_Bit_1StopBit_16MHZ_Clock_8X_Oversampling_No_DMA_No_Interupts (void) {

	USART_Config usartConfig = {0};

	usartConfig.baud_rate = 115200;
	usartConfig.clock_source_speed = 16000000;
	usartConfig.oversampling_mode = OVERSAMPLE_8X;
	usartConfig.use_tx_interrupt = false;
	usartConfig.use_rx_interrupt = false;

	configureUSARTDevice(usartDevice2, &usartConfig);

	TEST_ASSERT_EQUAL_HEX32(0x00000000, getUSARTDeviceCR1Value(usartDevice2));
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getUSARTDeviceCR2Value(usartDevice2));
	TEST_ASSERT_EQUAL_HEX32(0x00000113, getUSARTDeviceBRRValue(usartDevice2));
}

void test_USART_Enable_NO_DMA_NO_Interrupts (void) {
	enableUSARTDevice (usartDevice2);
	TEST_ASSERT_EQUAL_HEX32(0x0000000D, getUSARTDeviceCR1Value(usartDevice2));
}

void test_USART_Disable_NO_DMA_NO_Interrupts (void) {
	disableUSARTDevice (usartDevice2, false);
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getUSARTDeviceCR1Value(usartDevice2));
}
