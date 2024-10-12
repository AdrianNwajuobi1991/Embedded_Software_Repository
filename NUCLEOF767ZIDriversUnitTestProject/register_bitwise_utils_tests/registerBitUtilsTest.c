#include "unity.h"
#include "register_bit_utils.h"

extern volatile uint32_t registerVar;


void testSetBitInRegister (void) {

	registerSetBit(&registerVar, 0);
	registerSetBit(&registerVar, 1);
	TEST_ASSERT_EQUAL_HEX32(0x00000003, registerVar);
}

void testClearBitInRegister (void) {

	registerVar = 0x00000003;
	registerClearBit(&registerVar, 0);
	TEST_ASSERT_EQUAL_HEX32(0x00000002, registerVar);
}

void testToggleBitInRegister (void) {

	registerVar = 0x00000003;
	registerToggleBit(&registerVar, 1);
	TEST_ASSERT_EQUAL_HEX32(0x00000001, registerVar);
}

void testBitValueInRegister (void) {

	registerVar = 0x00000003;
	int bitValue = 0;

	bitValue = registerTestBitPosition(&registerVar, 2);
	TEST_ASSERT_EQUAL(BIT_CLEAR, bitValue);

	bitValue = registerTestBitPosition(&registerVar, 1);
	TEST_ASSERT_EQUAL(BIT_SET, bitValue);

	bitValue = registerTestBitPosition(&registerVar, 0);
	TEST_ASSERT_EQUAL(BIT_SET, bitValue);

	TEST_ASSERT_EQUAL_HEX32(0x00000003, registerVar);
}

void testSetValueInBitPositionInRegister (void) {

	registerVar = 0x00000003;
	registerSetValueInBitPosition(&registerVar, 9, 4);
	TEST_ASSERT_EQUAL_HEX32(0x00000093, registerVar);
}


void testClearValueInBitPositionInRegister (void) {

	registerVar = 0x00000093;
	registerClearValueInBitPosition(&registerVar, 3, 0);
	TEST_ASSERT_EQUAL_HEX32(0x00000090, registerVar);
}

void testToggleValueInBitPositionInRegister (void) {

	registerVar = 0x00000093;
	registerToggleValueInBitPosition(&registerVar, 147, 0);
	TEST_ASSERT_EQUAL_HEX32(0x00000000, registerVar);
}

void testMaskBitsInRegister (void) {

	registerVar = 0x00000093;
	unsigned int maskValue = 0;

	maskValue = registerGetMaskBits(&registerVar, 0xFF);
	TEST_ASSERT_EQUAL_HEX32(0x00000093, maskValue);

	maskValue = registerGetMaskBits(&registerVar, 0x0F);
	TEST_ASSERT_EQUAL_HEX32(0x00000003, maskValue);

	maskValue = registerGetMaskBits(&registerVar, 0xF0);
	TEST_ASSERT_EQUAL_HEX32(0x00000090, maskValue);
}

void testOverwriteValueInRegister (void) {

	registerVar = 0x00000093;
	registerOverwriteValue(&registerVar, 344);
	TEST_ASSERT_EQUAL_HEX32(0x00000158, registerVar);
}

void testGetValueOfRegister (void) {
	registerVar = 0x00452312;
	unsigned int registerValue = registerGetValue(&registerVar);
	TEST_ASSERT_EQUAL_HEX32(0x00452312, registerValue);
}


