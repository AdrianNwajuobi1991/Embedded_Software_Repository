/*
 * spi_integration_test.c
 *
 *  Created on: Jul 30, 2024
 *      Author: root
 */

#include "USART_Dependency_Injection.h"
#include "GPIO_Dependency_Injection.h"
#include "gpio_integration_test.h"
#include "gpio_integration_test.h"
#include "usart_integration_test.h"
#include "DMA_Dependency_Injection.h"
#include "TIMER_Driver.h"
#include "TIMER_Dependency_Injection.h"
#include <string.h>
#include <stdbool.h>
#include "stm32f767xx.h"


static usart_device usartDevice5 = 0;
static gpio_device gpioPortB = 0;

static dma_stream_device dmaStream;
static dma_device dmaDevice;
static timer_device timer7;

static unsigned char test_string[] = "Adrian Nwajuobi wrote the USART Driver !!!\n\r";
static unsigned char test_string_Circular_Mode[] = "Adrian Nwajuobi wrote the USART Driver Running in Circular Mode. !!!\n\r";

uint32_t position = 0;

static bool rxInProgress = false;

void test_usart2_rx_of_usart5_tx (void) {
	rxInProgress = true;
}

void test_tx_send_long_string_circular_mode (void) {
	DMA_Stream_Config dmaStreamConfig;

	DMA_transmit_setup (usartDevice5, (uint8_t *)test_string_Circular_Mode, sizeof(test_string_Circular_Mode), &dmaStreamConfig);

	dmaStreamConfig.priorityLevel = VERY_HIGH_PRIORITY;
	dmaStreamConfig.channelSelection = CHANNEL_FOUR;
	dmaStreamConfig.circularMode = ENABLE_CIRCULAR_MODE;
	dmaStreamConfig.doubleBufferMode = DISABLE_DOUBLE_BUFFER_MODE;
	dmaStreamConfig.fifoLevel = FULL_LEVEL_FIFO;
	dmaStreamConfig.fifoSetting = DISABLE_FIFO;

	dmaDisableTransmit (usartDevice5);
	disableDMAStream (dmaStream);
	configureDMAStream(dmaStream, dmaDevice, &dmaStreamConfig);
	enableDMAStream (dmaStream);
	dmaEnableTransmit (usartDevice5);
}

void test_tx_send_long_string (void) {

	DMA_Stream_Config dmaStreamConfig;

	DMA_transmit_setup (usartDevice5, (uint8_t *)test_string, sizeof(test_string), &dmaStreamConfig);

	dmaStreamConfig.priorityLevel = VERY_HIGH_PRIORITY;
	dmaStreamConfig.channelSelection = CHANNEL_FOUR;
	dmaStreamConfig.circularMode = DISABLE_CIRCULAR_MODE;
	dmaStreamConfig.doubleBufferMode = DISABLE_DOUBLE_BUFFER_MODE;
	dmaStreamConfig.fifoLevel = FULL_LEVEL_FIFO;
	dmaStreamConfig.fifoSetting = DISABLE_FIFO;

	dmaDisableTransmit (usartDevice5);
	disableDMAStream (dmaStream);
	configureDMAStream(dmaStream, dmaDevice, &dmaStreamConfig);
	enableDMAStream (dmaStream);
	dmaEnableTransmit (usartDevice5);
}

void test_tx_rx_basic_prompt (void) {

	//unsigned char prompt_string[] = {"\nEnter anything to be echoed back:\n "};
	//unsigned char user_data[100] = {0};
	//transmit_packet (usartDevice5, (uint8_t *) prompt_string, sizeof(prompt_string), false);
	//read user response
	//recieve_packet (usartDevice5, (uint8_t *) user_data, 6, false);
	//echo it back
	//transmit_packet (usartDevice5, (uint8_t *) user_data, sizeof(user_data), false, dmaStream, dmaDevice);
}

void setup_usart_integration_test (void) {
	Initialize_DMA1();
	initialize_USART5_Device();
	initialize_GPIO_PORTB();
	Initialize_TIMER7();

	dmaStream = getDMAStreamInstance(DMA_STREAM_7);
	dmaDevice = getDMADeviceInstance(DMA_1);
	usartDevice5 = getUSARTDeviceInstance(USART_INSTANCE_5);
	gpioPortB = getGPIODeviceInstance(PORTB);
	timer7 = getTimerDeviceInstance(TIM_7);

	GPIOPortConfiguration gpioPortBConfig;
	memset(&gpioPortBConfig, 0, sizeof(gpioPortBConfig));

	gpioPortBConfig.gpioModeConfiguration = ALT_FUNC_MODE;
	gpioPortBConfig.gpioOutputSpeedConfiguration = VERY_HIGH_SPEED;
	gpioPortBConfig.gpioOutputTypeConfiguration = PUSH_PULL;
	gpioPortBConfig.gpioPUPDConfiguration = NO_PULLUP_PULLDOWN;
	gpioPortBConfig.gpioAFRHConfiguration = AF7; //UART5 functions

	configureGPIODevice(gpioPortB, &gpioPortBConfig, PIN8); //RX Pin
	configureGPIODevice(gpioPortB, &gpioPortBConfig, PIN9); //TX Pin

	USART_Config usartConfig;
	usartConfig.baud_rate = 230400;
	usartConfig.clock_source_speed = 16000000;
	usartConfig.oversampling_mode = OVERSAMPLE_16X;
	usartConfig.use_tx_interrupt = false;

	usartConfig.use_rx_interrupt = false;
	usartConfig.use_error_interrupts = false;
	configureUSARTDevice (usartDevice5, &usartConfig);

	enableUSARTDevice (usartDevice5);

	disableTimer(timer7);

	configureTimeBaseGeneration (timer7, 15, 999);

	enableTimer(timer7);

}

usart_device getUsartDevice (void) {
	return usartDevice5;
}

void delayUSART(int ms) {
	checkAndClearTimerUpdateInterruptFlag(timer7);
	for(; ms>0 ;ms--) {
		checkAndClearTimerUpdateInterruptFlag(timer7);
	}
}
