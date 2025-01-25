#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H


#include "register_bit_utils.h"
#include <stdint.h>

typedef struct GPIO_TypeDef_t * gpio_device;

typedef struct GPIOPortConfiguration {
	uint8_t gpioModeConfiguration;
	uint8_t gpioOutputTypeConfiguration;
	uint8_t gpioOutputSpeedConfiguration;
	uint8_t gpioPUPDConfiguration;
	uint8_t gpioAFRLConfiguration;
	uint8_t gpioAFRHConfiguration;
}GPIOPortConfiguration;

enum {INPUT_MODE, GENERAL_PURPOSE_OUTPUT, ALT_FUNC_MODE, ANALOG_MODE};
enum {PUSH_PULL, OPEN_DRAIN};
enum {LOW_SPEED, MEDIUM_SPEED, HIGH_SPEED, VERY_HIGH_SPEED};
enum {NO_PULLUP_PULLDOWN, PULL_UP, PULL_DOWN};

enum {AF0, AF1, AF2, AF3, AF4, AF5, AF6, AF7, AF8, AF9, AF10, AF11,
	AF12, AF13, AF14, AF15
};

void configureGPIODevice(gpio_device device,
		GPIOPortConfiguration* config,
		uint16_t pinNumber);

void setGPIOPinNumberBSRR(gpio_device device, uint16_t pinNumber);

void resetGPIOPinNumberBSRR(gpio_device device, uint16_t pinNumber);

uint32_t readGPIOInputDataRegister(gpio_device device);

uint32_t readGPIOInputPin(gpio_device device, uint8_t pinNumber);

void setGPIOPortValue(gpio_device device, uint16_t portValue);

void resetGPIOPortValue(gpio_device device, uint16_t portValue);

void toggleGPIOPortValue (gpio_device device, uint16_t portValue);


#endif
