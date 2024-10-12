#include "GPIODriver.h"
#include "STM32F767ZIGPIODeviceLayout.h"
#include "GPIO_Device_Common.h"

#define MAX_GPIO_INSTANCE	5


static void configureGPIOAFRLRegisters(gpio_device device,
												GPIOPortConfiguration* config,
														uint16_t pinNumber);
static void configureGPIOPUPDRRegister(gpio_device device,
												GPIOPortConfiguration* config,
														uint16_t pinNumber);

static void configureGPIOOSPEEDRegister(gpio_device device,
												GPIOPortConfiguration* config,
														uint16_t pinNumber);

static void configureGPIOOTYPERegister(gpio_device device,
												GPIOPortConfiguration* config,
														uint16_t pinNumber);

static void configureGPIOMODERegister(gpio_device device,
												GPIOPortConfiguration* config,
														uint16_t pinNumber);

void configureGPIODevice(gpio_device device,
								GPIOPortConfiguration* config,
											 uint16_t pinNumber) {
	configureGPIOMODERegister(device, config, pinNumber);
	configureGPIOOTYPERegister(device, config, pinNumber);
	configureGPIOOSPEEDRegister(device, config, pinNumber);
	configureGPIOPUPDRRegister(device, config, pinNumber);
	configureGPIOAFRLRegisters(device, config, pinNumber);
}

uint32_t readGPIOInputDataRegister(gpio_device device) {
	return registerGetMaskBits(&device->IDR, 0xFFFF);
}

void setGPIOPinNumberBSRR(gpio_device device, uint16_t pinNumber) {
	registerSetBit(&device->BSRR, pinNumber);
}

void resetGPIOPinNumberBSRR(gpio_device device, uint16_t pinNumber) {
	registerSetBit(&device->BSRR, (pinNumber + 16));
}

static void configureGPIOMODERegister(gpio_device device,
												GPIOPortConfiguration* config,
														uint16_t pinNumber) {
	unsigned int maskBitsToClear = 0;
	maskBitsToClear = 0x3;
	registerClearValueInBitPosition(&device->MODER, maskBitsToClear, (pinNumber * 2));
	registerSetValueInBitPosition(&device->MODER, config->gpioModeConfiguration, (pinNumber * 2));
}

static void configureGPIOOTYPERegister(gpio_device device,
												GPIOPortConfiguration* config,
														uint16_t pinNumber) {
	unsigned int maskBitsToClear = 0;
	maskBitsToClear = 0x1;
	registerClearValueInBitPosition(&device->OTYPER, maskBitsToClear, pinNumber);
	registerSetValueInBitPosition(&device->OTYPER, config->gpioOutputTypeConfiguration, pinNumber);
}

static void configureGPIOOSPEEDRegister(gpio_device device,
												GPIOPortConfiguration* config,
														uint16_t pinNumber) {
	unsigned int maskBitsToClear = 0;
	maskBitsToClear = 0x3;
	registerClearValueInBitPosition(&device->OSPEEDR, maskBitsToClear, (pinNumber * 2));
	registerSetValueInBitPosition(&device->OSPEEDR, config->gpioOutputSpeedConfiguration, (pinNumber * 2));
}

static void configureGPIOPUPDRRegister(gpio_device device,
												GPIOPortConfiguration* config,
														uint16_t pinNumber) {
	unsigned int maskBitsToClear = 0;
	maskBitsToClear = 0x3;
	registerClearValueInBitPosition(&device->PUPDR, maskBitsToClear, (pinNumber * 2));
	registerSetValueInBitPosition(&device->PUPDR, config->gpioPUPDConfiguration, (pinNumber * 2));
}

static void configureGPIOAFRLRegisters(gpio_device device,
												GPIOPortConfiguration* config,
														uint16_t pinNumber) {
	if ((pinNumber >= PIN0) && (pinNumber <= PIN7)) {
		registerClearValueInBitPosition(&device->AFR[0], 0xF, (pinNumber * 4));
		registerSetValueInBitPosition(&device->AFR[0], config->gpioAFRLConfiguration, (pinNumber * 4));
	}

	if ((pinNumber >= PIN8) && (pinNumber <= PIN15)) {
		uint16_t pinNumberVar = pinNumber;
		pinNumberVar -= PIN8;
		registerClearValueInBitPosition(&device->AFR[1], 0xF, (pinNumberVar * 4));
		registerSetValueInBitPosition(&device->AFR[1], config->gpioAFRHConfiguration, (pinNumberVar * 4));
	}
}

void setGPIOPortValue(gpio_device device, uint16_t portValue) {
	registerOverwriteValue(&device->BSRR, portValue);
}

void resetGPIOPortValue(gpio_device device, uint16_t portValue) {
	registerOverwriteValue(&device->BSRR, (portValue << 16));
}

void toggleGPIOPortValue (gpio_device device, uint16_t portValue) {
	device->ODR ^= portValue;
}


