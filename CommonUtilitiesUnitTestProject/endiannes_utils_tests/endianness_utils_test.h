/*
 * endianness_test.h
 *
 *  Created on: Jul 31, 2024
 *      Author: root
 */

#ifndef ENDIANNESS_UTILS_TEST_H_
#define ENDIANNESS_UTILS_TEST_H_

void convertFromHostEndiannessToProtocolEndiannessDifferentEndianness (void);
void convertFromHostEndiannessToProtocolEndiannessSameEndianess (void);
void convertFromProtocolEndiannessToHostEndiannessDifferentEndianness (void);
void convertFromProtocolEndiannessToHostEndiannessSameEndianness (void);

#endif /* ENDIANNESS_UTILS_TEST_H_ */
