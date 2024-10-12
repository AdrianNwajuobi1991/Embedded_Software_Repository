#include "protocol_endian_debug_utils.h"

static void setProtocolEndiannessTesting(int* protocolEndiannessPointer, int debugEndiannesValue);

void (*setProtocolEndiannesDebug) (int* protocolEndiannessPointer, int debugEndiannesValue) = setProtocolEndiannessTesting;

static void setProtocolEndiannessTesting(int* protocolEndiannessPointer, int debugEndiannesValue) {
	*protocolEndiannessPointer = debugEndiannesValue;
}

