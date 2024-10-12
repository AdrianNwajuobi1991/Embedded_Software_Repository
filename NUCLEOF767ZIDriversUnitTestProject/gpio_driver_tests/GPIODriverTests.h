#ifndef GPIO_DRIVER_TEST_H
#define GPIO_DRIVER_TEST_H

void test_GPIODriverCreationGPIOPORTAANDBInstances (void);

void test_GPIODriverGPIOPORTARCCEnabledOnCreate (void);

void test_GPIODriverGPIOPORTBRCCEnabledOnCreate (void);

void test_GPIODriverGPIOPORTAConfigureMODEToGPIOOperation (void);

void test_GPIODriverGPIOPORTBConfigureMODEToGPIOOperation (void);

void test_GPIOPORTAConfigureMODEToAlternateFunctionOperation (void);

void test_GPIOPORTBConfigureMODEToAlternateFunctionOperation (void);

void test_GPIOPORTAConfigureOutputTypeToOpenDrain (void);

void test_GPIOPORTBConfigureOutputTypeToOpenDrain (void);

void test_GPIOPORTAConfigureOutputSpeed (void);

void test_GPIOPORTAConfigureOutputSpeedTwoDifferentSpeedsSamePin (void);

void test_GPIOPORTBConfigureOutputSpeed (void);

void test_GPIOPORTAConfigureForPullUp (void);

void test_GPIOPORTBConfigureForPullDown (void);

void test_GPIOPORTAReadInputDataRegister (void);

void test_GPIOPORTBReadInputDataRegister (void);

void test_GPIOPORTABitSetResetRegisterSetPIN6 (void);

void test_GPIOPORTABitSetResetRegisterResetPIN6 (void);

void test_GPIOPORTBBitSetResetRegisterSetPIN6 (void);

void test_GPIOPORTBBitSetResetRegisterResetPIN6 (void);

void test_GPIOPORTAAlternateFunctionLowRegisterPIN2AlternateFunction (void);

void test_GPIOPORTAAlternateFunctionHighRegisterPIN10AlternateFunction (void);

void test_GPIOPORTBAlternateFunctionLowRegisterPIN2AlternateFunction (void);

void test_GPIOPORTBAlternateFunctionHighRegisterPIN10AlternateFunction (void);

void test_GPIOPORTBAlternateFunctionHighRegisterPIN14PIN15Simultaneous (void);

void test_GPIOPORTB_SetGPIO_PORTB_TO_GIVEN_VALUE (void);

void test_GPIOPORTB_ClearGPIO_PORTB_OF_GIVEN_VALUE (void);

#endif
