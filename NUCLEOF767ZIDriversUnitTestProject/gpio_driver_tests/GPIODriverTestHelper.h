#ifndef GPIO_DRIVER_TEST_HELPER_H
#define GPIO_DRIVER_TEST_HELPER_H

#include "GPIODriver.h"


unsigned int getGPIODeviceMODERegisterValue(gpio_device device);

unsigned int getGPIODeviceOutputTypeRegisterValue(gpio_device device);

unsigned int getGPIODeviceOutputSpeedRegisterValue(gpio_device device);

unsigned int getGPIODevicePUPDRegisterValue(gpio_device device);

unsigned int getGPIOBitSetResetRegister(gpio_device device);

unsigned int getGPIODeviceAFRLRegister(gpio_device device);

unsigned int getGPIODeviceAFRHRegister(gpio_device device);

void setGPIOInputDataRegister(gpio_device device, unsigned int value);

#endif
