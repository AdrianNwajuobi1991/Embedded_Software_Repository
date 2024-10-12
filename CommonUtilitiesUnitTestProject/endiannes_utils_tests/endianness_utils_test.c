/*
 * endianness_test.c
 *
 *  Created on: Jul 31, 2024
 *      Author: root
 */

#include "unity.h"
#include "endianness_utils_test.h"
#include "protocol_endian_utils.h"
#include "protocol_endian_debug_utils.h"


void setUp (void)
{
	protocol_endian_utils_setup();
}

void tearDown (void)
{
	protocol_endian_utils_teardown();
}

/*
 * Test to convert multi byte data from machine endianness to protocol endianness
 * where host and protocol endianness differs
 */

void convertFromHostEndiannessToProtocolEndiannessDifferentEndianness (void)
{
	unsigned int hostData = 0x76543210; //data to be converted from host
	//int hostDataCopy = 0x76543210;
	hostToProtocolEndiannessConvert(&hostData, sizeof(unsigned int)); // convert to the endianness of the protocol.
	TEST_ASSERT_EQUAL_HEX32(0x10325476, hostData);
}

void convertFromHostEndiannessToProtocolEndiannessSameEndianess (void)
{
	unsigned int hostData = 0x76543210; //data to be converted from host
	//int hostDataCopy = 0x76543210;
	//debug set the protocol endianness here to little endian for testing purposes. Otherwise this test will always fail.
	setProtocolEndiannesDebug(getProtocolEndianness(),LITTLE_ENDIAN_DEBUG);
	hostToProtocolEndiannessConvert(&hostData, sizeof(unsigned int)); // convert to the endianness of the protocol.
	TEST_ASSERT_EQUAL_HEX32(0x76543210, hostData); // should should be the same value if host and protocol endianness is the same
}

void convertFromProtocolEndiannessToHostEndiannessDifferentEndianness (void)
{
	unsigned int protocolData = 0x10325476; //data to be converted Protocol
	//int hostDataCopy = 0x76543210;
	protocolToHostEndiannessConvert(&protocolData, sizeof(unsigned int)); // convert to the endianness of the protocol.
	TEST_ASSERT_EQUAL_HEX32(0x76543210, protocolData);

}

void convertFromProtocolEndiannessToHostEndiannessSameEndianness (void)
{
	unsigned int protocolData = 0x10325476; //data to be converted Protocol
	//int hostDataCopy = 0x76543210;
	//debug set the protocol endianness here to little endian for testing purposes. Otherwise this test will always fail.
	setProtocolEndiannesDebug(getProtocolEndianness(),LITTLE_ENDIAN_DEBUG);
	protocolToHostEndiannessConvert(&protocolData, sizeof(unsigned int)); // convert to the endianness of the protocol.
	TEST_ASSERT_EQUAL_HEX32(0x10325476, protocolData);

}

