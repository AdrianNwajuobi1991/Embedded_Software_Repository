/*
 * TIMER_Test_Dependency_Injection.c
 *
 *  Created on: Aug 24, 2024
 *      Author: root
 */

#include "TIMER_Dependency_Injection.h"
#include <string.h>


static TIM_TypeDef_t timerDevices[3];


timer_device getTimerDeviceInstance (int instance) {
	timerDevices[instance].ARR = 0xFFFF;
	return &timerDevices[instance];

}

void TimerDeviceInstanceCleanUp (timer_device device, PWM_TIMER_Config * config) {
	memset(device, TIMER_DEFAULT_SETTING, sizeof(TIM_TypeDef_t));
	device->ARR = 0xFFFF;
}
