/*
 * unit_tests_setup_teardown.c
 *
 *  Created on: Jul 30, 2024
 *      Author: root
 */

#include "unity.h"

#include "GPIODriver.h"
#include "GPIO_Dependency_Injection.h"
#include "SPIDriver.h"
#include "SPI_Dependency_Injection.h"
#include "I2CDriver.h"
#include "I2C_Dependency_Injection.h"
#include "GPIO_Device_Common.h"
#include "USART_Driver.h"
#include "USART_Dependency_Injection.h"
#include "DMA_Driver.h"
#include "DMA_Dependency_Injection.h"
#include "FLASH_Driver.h"
#include "FLASH_Dependency_Injection.h"
#include "TIMER_Driver.h"
#include "TIMER_Dependency_Injection.h"
#include "RCC_Driver.h"
#include "RCC_Dependency_Injection.h"
#include "PWRControlDriver.h"
#include "PWRControl_Dependency_Injection.h"
#include "RTC_Driver.h"
#include "RTC_Driver_Dependency_Injection.h"

spi_device spiDevice;
gpio_device gpioDevicePORTA;
gpio_device gpioDevicePORTB;
volatile uint32_t registerVar;
i2c_device i2cDevice1;
usart_device usartDevice2;
dma_stream_device dmaStream;
dma_device dmaDevice;
flash_device flashDevice;
timer_device timerDevice;
rcc_device rccDevice;
power_control_device powerControlDevice;
rtc_device rtcDevice;


void setUp (void) {
	spiDevice = getSPIDeviceInstance(SPI_INSTANCE_1);
	gpioDevicePORTA = getGPIODeviceInstance(PORTA);
	gpioDevicePORTB = getGPIODeviceInstance(PORTB);
	registerVar = 0;
	i2cDevice1 = getI2CDeviceInstance(I2C_1);
	usartDevice2 = getUSARTDeviceInstance(USART_INSTANCE_5);
	dmaStream = getDMAStreamInstance(DMA_STREAM_0);
	dmaDevice = getDMADeviceInstance(DMA_1);
	flashDevice = getFlashDeviceInstance();
	timerDevice = getTimerDeviceInstance(TIM_1);
	rccDevice = getRCCDeviceInstance();
	powerControlDevice = getPowerControlDeviceInstance();
	rtcDevice = getRTCDeviceInstance();
}

void tearDown (void) {
	spiDeviceCleanUp(spiDevice, (SPI_Config *)0);
	GPIODeviceCleanUp(gpioDevicePORTA, (GPIOPortConfiguration *)0);
	GPIODeviceCleanUp(gpioDevicePORTB, (GPIOPortConfiguration *)0);
	registerVar = 0;
	I2CDeveiceCleanUp(i2cDevice1, (I2C_Config *)0);
	USARTDeviceCleanUp(usartDevice2, (USART_Config *)0);
	DMAStreamDeviceCleanUp(dmaStream, (DMA_Stream_Config *)0);
	DMADeviceCleanUp(dmaDevice);
	FlashDeviceInstanceCleanUp();
	TimerDeviceInstanceCleanUp(timerDevice, (PWM_TIMER_Config *)0);
	RCC_DeviceInstanceCleanUp();
	PowerControlDeviceInstanceCleanUp();
	RTCDeviceInstanceCleanUp();
}

