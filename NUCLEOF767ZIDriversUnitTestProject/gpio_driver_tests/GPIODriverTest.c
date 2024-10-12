
#include "GPIODriver.h"

#include "unity.h"
#include "GPIODriverTestHelper.h"
#include "GPIODriverTests.h"
#include "GPIO_Dependency_Injection.h"
#include "GPIO_Device_Common.h"

extern gpio_device gpioDevicePORTA;
extern gpio_device gpioDevicePORTB;

void test_GPIODriverCreationGPIOPORTAANDBInstances (void) {

	TEST_ASSERT_NOT_EQUAL(0, gpioDevicePORTA);
	TEST_ASSERT_EQUAL_UINT32(0xA8000000, getGPIODeviceMODERegisterValue(gpioDevicePORTA));

	TEST_ASSERT_NOT_EQUAL(0, gpioDevicePORTB);
	TEST_ASSERT_EQUAL_HEX32( 0x00000280, getGPIODeviceMODERegisterValue(gpioDevicePORTB));
}

void test_GPIODriverGPIOPORTAConfigureMODEToGPIOOperation (void) {

	GPIOPortConfiguration config;
	config.gpioModeConfiguration = GENERAL_PURPOSE_OUTPUT;
	//config.gpioPinNumber = PIN0;
	//register state prior to configuration
	TEST_ASSERT_EQUAL_HEX32(0xA8000000, getGPIODeviceMODERegisterValue(gpioDevicePORTA));
	configureGPIODevice(gpioDevicePORTA, &config, PIN0);
	//register state after configuration
	TEST_ASSERT_EQUAL_HEX32(0xA8000001, getGPIODeviceMODERegisterValue(gpioDevicePORTA));
}

void test_GPIODriverGPIOPORTBConfigureMODEToGPIOOperation (void) {

	GPIOPortConfiguration config;
	config.gpioModeConfiguration = GENERAL_PURPOSE_OUTPUT;
	//config.gpioPinNumber = PIN0;
	//register state prior to configuration
	TEST_ASSERT_EQUAL_HEX32(0x00000280, getGPIODeviceMODERegisterValue(gpioDevicePORTB));
	configureGPIODevice(gpioDevicePORTB, &config, PIN0);
	//register state after configuration
	TEST_ASSERT_EQUAL_HEX32(0x00000281, getGPIODeviceMODERegisterValue(gpioDevicePORTB));
}


void test_GPIOPORTAConfigureMODEToAlternateFunctionOperation (void) {

	GPIOPortConfiguration config;
	config.gpioModeConfiguration = ALT_FUNC_MODE;
	//config.gpioPinNumber = PIN4;
	//register state prior to configuration
	TEST_ASSERT_EQUAL_HEX32(0xA8000000, getGPIODeviceMODERegisterValue(gpioDevicePORTA));
	configureGPIODevice(gpioDevicePORTA, &config, PIN4);
	//register state after configuration
	TEST_ASSERT_EQUAL_HEX32(0xA8000200, getGPIODeviceMODERegisterValue(gpioDevicePORTA));
}


void test_GPIOPORTBConfigureMODEToAlternateFunctionOperation (void) {

	GPIOPortConfiguration config;
	config.gpioModeConfiguration = ALT_FUNC_MODE;
	//config.gpioPinNumber = PIN15;
	//register state prior to configuration
	TEST_ASSERT_EQUAL_HEX32(0x00000280, getGPIODeviceMODERegisterValue(gpioDevicePORTB));
	configureGPIODevice(gpioDevicePORTB, &config, PIN15);
	//register state after configuration
	TEST_ASSERT_EQUAL_HEX32(0x80000280, getGPIODeviceMODERegisterValue(gpioDevicePORTB));
}


void test_GPIOPORTAConfigureOutputTypeToOpenDrain (void) {
	GPIOPortConfiguration config;
	config.gpioOutputTypeConfiguration = OPEN_DRAIN;
	//config.gpioPinNumber = PIN7;
	//register state prior to configuration
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getGPIODeviceOutputTypeRegisterValue(gpioDevicePORTA));
	configureGPIODevice(gpioDevicePORTA, &config, PIN7);
	//register state after configuration
	TEST_ASSERT_EQUAL_HEX32(0x00000080, getGPIODeviceOutputTypeRegisterValue(gpioDevicePORTA));
}

void test_GPIOPORTBConfigureOutputTypeToOpenDrain (void) {
	GPIOPortConfiguration config;
	config.gpioOutputTypeConfiguration = OPEN_DRAIN;
	//config.gpioPinNumber = PIN10;
	//register state prior to configuration
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getGPIODeviceOutputTypeRegisterValue(gpioDevicePORTB));
	configureGPIODevice(gpioDevicePORTB, &config, PIN10);
	//register state after configuration
	TEST_ASSERT_EQUAL_HEX32(0x00000400, getGPIODeviceOutputTypeRegisterValue(gpioDevicePORTB));
}

void test_GPIOPORTAConfigureOutputSpeed (void) {
	GPIOPortConfiguration config;
	config.gpioOutputSpeedConfiguration = HIGH_SPEED;
	//register state prior to configuration
	TEST_ASSERT_EQUAL_HEX32(0x0C000000, getGPIODeviceOutputSpeedRegisterValue(gpioDevicePORTA));
	configureGPIODevice(gpioDevicePORTA, &config, PIN4);
	//register state after configuration
	TEST_ASSERT_EQUAL_HEX32(0x0C000200, getGPIODeviceOutputSpeedRegisterValue(gpioDevicePORTA));
}

void test_GPIOPORTAConfigureOutputSpeedTwoDifferentSpeedsSamePin (void) {
	GPIOPortConfiguration config;
	config.gpioOutputSpeedConfiguration = HIGH_SPEED;
	//register state prior to configuration
	TEST_ASSERT_EQUAL_HEX32(0x0C000000, getGPIODeviceOutputSpeedRegisterValue(gpioDevicePORTA));
	configureGPIODevice(gpioDevicePORTA, &config, PIN4);
	//register state after configuration
	TEST_ASSERT_EQUAL_HEX32(0x0C000200, getGPIODeviceOutputSpeedRegisterValue(gpioDevicePORTA));

	config.gpioOutputSpeedConfiguration = LOW_SPEED;
	configureGPIODevice(gpioDevicePORTA, &config, PIN4);
	//register state after configuration
	TEST_ASSERT_EQUAL_HEX32(0x0C000000, getGPIODeviceOutputSpeedRegisterValue(gpioDevicePORTA));

}

void test_GPIOPORTBConfigureOutputSpeed (void) {
	GPIOPortConfiguration config;
	config.gpioOutputSpeedConfiguration = VERY_HIGH_SPEED;
	//register state prior to configuration
	TEST_ASSERT_EQUAL_HEX32(0x000000C0, getGPIODeviceOutputSpeedRegisterValue(gpioDevicePORTB));
	configureGPIODevice(gpioDevicePORTB, &config, PIN12);
	//register state after configuration
	TEST_ASSERT_EQUAL_HEX32(0x030000C0, getGPIODeviceOutputSpeedRegisterValue(gpioDevicePORTB));
}

void test_GPIOPORTAConfigureForPullUp (void) {
	GPIOPortConfiguration config;
	config.gpioPUPDConfiguration = PULL_UP;
	//register state prior to configuration
	TEST_ASSERT_EQUAL_HEX32(0x64000000, getGPIODevicePUPDRegisterValue(gpioDevicePORTA));
	configureGPIODevice(gpioDevicePORTA, &config, PIN11);
	//register state after configuration
	TEST_ASSERT_EQUAL_HEX32(0x64400000, getGPIODevicePUPDRegisterValue(gpioDevicePORTA));
}

void test_GPIOPORTBConfigureForPullDown (void) {
	GPIOPortConfiguration config;
	config.gpioPUPDConfiguration = PULL_DOWN;
	//register state prior to configuration
	TEST_ASSERT_EQUAL_HEX32(0x00000100, getGPIODevicePUPDRegisterValue(gpioDevicePORTB));
	configureGPIODevice(gpioDevicePORTB, &config, PIN11);
	//register state after configuration
	TEST_ASSERT_EQUAL_HEX32(0x00800100, getGPIODevicePUPDRegisterValue(gpioDevicePORTB));
}

void test_GPIOPORTAReadInputDataRegister (void) {
	unsigned int gpioInputData = 0;

	setGPIOInputDataRegister(gpioDevicePORTA, 0xA8340020);

	gpioInputData = readGPIOInputDataRegister(gpioDevicePORTA);

	TEST_ASSERT_EQUAL_HEX32(0x00000020, gpioInputData);

	setGPIOInputDataRegister(gpioDevicePORTA, 0xA8340080);

	gpioInputData = readGPIOInputDataRegister(gpioDevicePORTA);

	TEST_ASSERT_EQUAL_HEX32(0x00000080, gpioInputData);
}


void test_GPIOPORTBReadInputDataRegister (void) {
	unsigned int gpioInputData = 0;

	setGPIOInputDataRegister(gpioDevicePORTB, 0xA8340020);

	gpioInputData = readGPIOInputDataRegister(gpioDevicePORTB);

	TEST_ASSERT_EQUAL_HEX32(0x00000020, gpioInputData);

	setGPIOInputDataRegister(gpioDevicePORTB, 0xA8340080);

	gpioInputData = readGPIOInputDataRegister(gpioDevicePORTB);

	TEST_ASSERT_EQUAL_HEX32(0x00000080, gpioInputData);
}


void test_GPIOPORTABitSetResetRegisterSetPIN6 (void) {
	unsigned int gpioBitSetResetRegisterValue = 0;

	gpioBitSetResetRegisterValue = getGPIOBitSetResetRegister(gpioDevicePORTA);

	TEST_ASSERT_EQUAL_HEX32(0x00000000, gpioBitSetResetRegisterValue);

	setGPIOPinNumberBSRR(gpioDevicePORTA, PIN6);

	gpioBitSetResetRegisterValue = getGPIOBitSetResetRegister(gpioDevicePORTA);

	TEST_ASSERT_EQUAL_HEX32(0x00000040, gpioBitSetResetRegisterValue);
}


void test_GPIOPORTABitSetResetRegisterResetPIN6 (void) {
	unsigned int gpioBitSetResetRegisterValue = 0;

	gpioBitSetResetRegisterValue = getGPIOBitSetResetRegister(gpioDevicePORTA);

	TEST_ASSERT_EQUAL_HEX32(0x00000000, gpioBitSetResetRegisterValue);

	resetGPIOPinNumberBSRR(gpioDevicePORTA, PIN6);

	gpioBitSetResetRegisterValue = getGPIOBitSetResetRegister(gpioDevicePORTA);

	TEST_ASSERT_EQUAL_HEX32(0x00400000, gpioBitSetResetRegisterValue);
}

void test_GPIOPORTBBitSetResetRegisterSetPIN6 (void) {
	unsigned int gpioBitSetResetRegisterValue = 0;

	gpioBitSetResetRegisterValue = getGPIOBitSetResetRegister(gpioDevicePORTB);

	TEST_ASSERT_EQUAL_HEX32(0x00000000, gpioBitSetResetRegisterValue);

	setGPIOPinNumberBSRR(gpioDevicePORTB, PIN6);

	gpioBitSetResetRegisterValue = getGPIOBitSetResetRegister(gpioDevicePORTB);

	TEST_ASSERT_EQUAL_HEX32(0x00000040, gpioBitSetResetRegisterValue);
}


void test_GPIOPORTBBitSetResetRegisterResetPIN6 (void) {
	unsigned int gpioBitSetResetRegisterValue = 0;

	gpioBitSetResetRegisterValue = getGPIOBitSetResetRegister(gpioDevicePORTB);

	TEST_ASSERT_EQUAL_HEX32(0x00000000, gpioBitSetResetRegisterValue);

	resetGPIOPinNumberBSRR(gpioDevicePORTB, PIN6);

	gpioBitSetResetRegisterValue = getGPIOBitSetResetRegister(gpioDevicePORTB);

	TEST_ASSERT_EQUAL_HEX32(0x00400000, gpioBitSetResetRegisterValue);
}

void test_GPIOPORTAAlternateFunctionLowRegisterPIN2AlternateFunction (void) {
	GPIOPortConfiguration config;
	config.gpioAFRLConfiguration = AF5;

	configureGPIODevice(gpioDevicePORTA, &config, PIN2);

	TEST_ASSERT_EQUAL_HEX32(0x00000500, getGPIODeviceAFRLRegister(gpioDevicePORTA));
}

void test_GPIOPORTAAlternateFunctionHighRegisterPIN10AlternateFunction (void) {
	GPIOPortConfiguration config;
	config.gpioAFRHConfiguration = AF5;

	configureGPIODevice(gpioDevicePORTA, &config, PIN10);

	TEST_ASSERT_EQUAL_HEX32(0x00000500, getGPIODeviceAFRHRegister(gpioDevicePORTA));
}

void test_GPIOPORTBAlternateFunctionLowRegisterPIN2AlternateFunction (void) {
	GPIOPortConfiguration config;
	config.gpioAFRLConfiguration = AF5;

	configureGPIODevice(gpioDevicePORTB, &config, PIN2);

	TEST_ASSERT_EQUAL_HEX32(0x00000500, getGPIODeviceAFRLRegister(gpioDevicePORTB));
}

void test_GPIOPORTBAlternateFunctionHighRegisterPIN10AlternateFunction (void) {
	GPIOPortConfiguration config;
	config.gpioAFRHConfiguration = AF5;

	configureGPIODevice(gpioDevicePORTB, &config, PIN10);

	TEST_ASSERT_EQUAL_HEX32(0x00000500, getGPIODeviceAFRHRegister(gpioDevicePORTB));
}

void test_GPIOPORTBAlternateFunctionHighRegisterPIN14PIN15Simultaneous (void) {
	GPIOPortConfiguration gpioPortBConfig = {0};
	TEST_ASSERT_EQUAL_HEX32(0x00000000, gpioPortBConfig.gpioModeConfiguration);
	TEST_ASSERT_EQUAL_HEX32(0x00000000, gpioPortBConfig.gpioOutputTypeConfiguration);
	TEST_ASSERT_EQUAL_HEX32(0x00000000, gpioPortBConfig.gpioOutputSpeedConfiguration);
	TEST_ASSERT_EQUAL_HEX32(0x00000000, gpioPortBConfig.gpioPUPDConfiguration);
	TEST_ASSERT_EQUAL_HEX32(0x00000000, gpioPortBConfig.gpioAFRHConfiguration);

	gpioPortBConfig.gpioModeConfiguration = ALT_FUNC_MODE;
	gpioPortBConfig.gpioOutputTypeConfiguration = PUSH_PULL;
	gpioPortBConfig.gpioOutputSpeedConfiguration = HIGH_SPEED;
	gpioPortBConfig.gpioPUPDConfiguration = PULL_UP;
	gpioPortBConfig.gpioAFRHConfiguration = AF4;
	configureGPIODevice(gpioDevicePORTB, &gpioPortBConfig, PIN14);
	configureGPIODevice(gpioDevicePORTB, &gpioPortBConfig, PIN15);

	TEST_ASSERT_EQUAL_HEX32(0x00000000, getGPIODeviceOutputTypeRegisterValue(gpioDevicePORTB)); //00000000000000000000000000000000
	TEST_ASSERT_EQUAL_HEX32(0xA0000280, getGPIODeviceMODERegisterValue(gpioDevicePORTB)); //10100000000000000000001010000000
	TEST_ASSERT_EQUAL_HEX32(0xA00000C0, getGPIODeviceOutputSpeedRegisterValue(gpioDevicePORTB)); //10100000000000000000000011000000
	TEST_ASSERT_EQUAL_HEX32(0x50000100, getGPIODevicePUPDRegisterValue(gpioDevicePORTB)); //01010000000000000000000100000000
	TEST_ASSERT_EQUAL_HEX32(0x44000000, getGPIODeviceAFRHRegister(gpioDevicePORTB)); //01000100000000000000000000000000
}

void test_GPIOPORTB_SetGPIO_PORTB_TO_GIVEN_VALUE (void) {
	setGPIOPortValue(gpioDevicePORTB, 0xFC);

	uint32_t gpioBitSetResetRegisterValue = getGPIOBitSetResetRegister(gpioDevicePORTB);

	TEST_ASSERT_EQUAL_HEX32(0x000000FC, gpioBitSetResetRegisterValue);
}

void test_GPIOPORTB_ClearGPIO_PORTB_OF_GIVEN_VALUE (void) {
	resetGPIOPortValue(gpioDevicePORTB, 0xFC);

	uint32_t gpioBitSetResetRegisterValue = getGPIOBitSetResetRegister(gpioDevicePORTB);

	TEST_ASSERT_EQUAL_HEX32((0x000000FC << 16), gpioBitSetResetRegisterValue);
}

