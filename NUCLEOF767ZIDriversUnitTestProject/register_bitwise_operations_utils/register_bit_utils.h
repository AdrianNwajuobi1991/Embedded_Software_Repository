#ifndef REGISTER_BIT_UTILS_H
#define	REGISTER_BIT_UTILS_H

#include <stdint.h>

#define BIT_SET		1
#define	BIT_CLEAR	0

void registerSetBit (volatile uint32_t * registerAddr, uint8_t bitPostion);
void registerClearBit (volatile uint32_t * registerAddr, uint8_t bitPostion);
void registerToggleBit (volatile uint32_t * registerAddr, uint8_t bitPostion);
uint32_t registerTestBitPosition (volatile uint32_t * registerAddr, uint8_t bitPostion);
void registerSetValueInBitPosition (volatile uint32_t * registerAddr, uint32_t value, uint8_t bitPostion);
void registerClearValueInBitPosition (volatile uint32_t * registerAddr,	uint32_t value, uint8_t bitPostion);
void registerToggleValueInBitPosition (volatile uint32_t * registerAddr, uint32_t value, uint8_t bitPostion);
uint32_t registerGetMaskBits (volatile uint32_t * registerAddr,	uint32_t mask);
void registerOverwriteValue (volatile uint32_t * registerAddr, uint32_t value);
uint32_t registerGetValue(volatile uint32_t * registerAddr);

#endif
