/*
 * protocol_endian_utils.h
 *
 *  Created on: Oct 31, 2023
 *      Author: adrian
 */

#ifndef SANDBOX_INCLUDE_ENDIAN_UTILS_PROTOCOL_ENDIAN_UTILS_H_
#define SANDBOX_INCLUDE_ENDIAN_UTILS_PROTOCOL_ENDIAN_UTILS_H_

void protocol_endian_utils_setup(void);

void protocol_endian_utils_teardown(void);

void hostToProtocolEndiannessConvert(void* data, int length);

void protocolToHostEndiannessConvert(void* data, int length);

int * getProtocolEndianness(void);



#endif /* SANDBOX_INCLUDE_ENDIAN_UTILS_PROTOCOL_ENDIAN_UTILS_H_ */
