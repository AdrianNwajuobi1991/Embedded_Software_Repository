/*
 ============================================================================
 Name        : CommonUtilitiesUnitTestProject.c
 Author      : Adrian Nwajuobi
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "unity.h"
#include "endianness_utils_test.h"

int main(void) {
	UNITY_BEGIN();

	RUN_TEST (convertFromHostEndiannessToProtocolEndiannessDifferentEndianness);
	RUN_TEST (convertFromHostEndiannessToProtocolEndiannessSameEndianess);
	RUN_TEST (convertFromProtocolEndiannessToHostEndiannessDifferentEndianness);
	RUN_TEST (convertFromProtocolEndiannessToHostEndiannessSameEndianness);

	return UNITY_END();
}
