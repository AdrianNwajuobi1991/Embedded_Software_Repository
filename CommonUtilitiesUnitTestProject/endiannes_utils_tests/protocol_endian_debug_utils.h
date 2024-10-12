/*
 * protocol_endian_debug_utils.h
 *
 *  Created on: Nov 2, 2023
 *      Author: adrian
 */

#ifndef SANDBOX_INCLUDE_ENDIAN_UTILS_PROTOCOL_ENDIAN_DEBUG_UTILS_H_
#define SANDBOX_INCLUDE_ENDIAN_UTILS_PROTOCOL_ENDIAN_DEBUG_UTILS_H_
/*
 * this debug interface also includes the main production code header file for use in testing
 */

#include "protocol_endian_utils.h"

enum {BIG_ENDIAN_DEBUG, LITTLE_ENDIAN_DEBUG};

/*
 * debug function pointer in a separate debug header so as to not pollute the main production code
 * interface header file.
 */
extern void (*setProtocolEndiannesDebug) (int* protocolEndiannessPointer, int debugEndiannesValue);



#endif /* SANDBOX_INCLUDE_ENDIAN_UTILS_PROTOCOL_ENDIAN_DEBUG_UTILS_H_ */
