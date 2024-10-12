/*
 * floating_point_utils.c
 *
 *  Created on: Sep 19, 2024
 *      Author: root
 */

#include "floating_point_utils.h"
#include <stdint.h>

void enable_fpu_processor (void) {
	volatile uint32_t * CPACR = (volatile uint32_t *)0xE000ED88;
	*CPACR |= (0x3 << 22)|(0x3 << 20);
}
