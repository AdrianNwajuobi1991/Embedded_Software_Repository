#include "protocol_endian_utils.h"

enum {BIG_ENDIAN, LITTLE_ENDIAN, SAME_ENDIANNESS, DIFFERENT_ENDIANNESS};
/*
 * internal state variables for the module
 */
static int protocolEndianness = -1;
static int machineEndianness = -1;

static int machine_endianTest (void);

static int compareHostAndProtocolEndianness(void);

static void alterDataEndianness(void * data, int length);

void protocol_endian_utils_setup(void) {
	protocolEndianness = BIG_ENDIAN;
	machineEndianness = machine_endianTest();
}

void protocol_endian_utils_teardown(void) {
	protocolEndianness = -1;
	machineEndianness = -1;
}

void hostToProtocolEndiannessConvert(void * data, int length) {

	if (compareHostAndProtocolEndianness() == SAME_ENDIANNESS) {
		return;
	}else{
		alterDataEndianness(data, length);
	}

}

void protocolToHostEndiannessConvert(void * data, int length) {
	if (compareHostAndProtocolEndianness() == SAME_ENDIANNESS) {
		return;
	}else{
		alterDataEndianness(data, length);
	}
}

int * getProtocolEndianness(void) {
	return &protocolEndianness;
}

static int machine_endianTest (void){
	unsigned int testNumber = 0x00000001;
	unsigned char * firstByte = (unsigned char *)&testNumber;
	return (int)*firstByte;
}

static int compareHostAndProtocolEndianness(void){
	if (machineEndianness == protocolEndianness){
		return SAME_ENDIANNESS;
	}
	return DIFFERENT_ENDIANNESS;
}

static void alterDataEndianness(void * data, int length) {
	int firstElementIndex = 0;
	int lastElementIndex = length -1;
	unsigned char swapChar;
	unsigned char * uCharPtr = (unsigned char *)data;

	while (firstElementIndex < lastElementIndex) {
		swapChar = uCharPtr[firstElementIndex];
		uCharPtr[firstElementIndex] = uCharPtr[lastElementIndex];
		uCharPtr[lastElementIndex] = swapChar;
		firstElementIndex++;
		lastElementIndex--;
	}
}


