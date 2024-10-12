#include "register_bit_utils.h"


void registerSetBit(volatile uint32_t * registerAddr, uint8_t bitPostion) {
	(*(registerAddr)) |= (1 << bitPostion);
}

void registerClearBit (volatile uint32_t * registerAddr, uint8_t bitPostion) {
	(*(registerAddr)) &= ~(1 << bitPostion);
}

void registerToggleBit (volatile uint32_t * registerAddr, uint8_t bitPostion) {
	(*(registerAddr)) ^= (1 << bitPostion);
}

uint32_t registerTestBitPosition (volatile uint32_t * registerAddr, uint8_t bitPostion) {

	return (((*registerAddr) & (1 << bitPostion)) >> bitPostion);
}

void registerSetValueInBitPosition (volatile uint32_t * registerAddr, uint32_t value, uint8_t bitPostion) {
	(*(registerAddr)) |= (value << bitPostion);
}

void registerClearValueInBitPosition (volatile uint32_t * registerAddr,	uint32_t value, uint8_t bitPostion) {
	(*(registerAddr)) &= ~(value << bitPostion);
}

void registerToggleValueInBitPosition (volatile uint32_t * registerAddr, uint32_t value, uint8_t bitPostion) {
	(*(registerAddr)) ^= (value << bitPostion);
}

uint32_t registerGetMaskBits (volatile uint32_t * registerAddr,	uint32_t mask) {
	return ((*(registerAddr)) & (mask));
}

void registerOverwriteValue (volatile uint32_t * registerAddr, uint32_t value) {
	(*(registerAddr)) = value;
}

uint32_t registerGetValue(volatile uint32_t * registerAddr) {
	return (*(registerAddr));
}
