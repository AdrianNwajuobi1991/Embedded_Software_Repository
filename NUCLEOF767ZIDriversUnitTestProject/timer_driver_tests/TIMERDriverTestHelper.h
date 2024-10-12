/*
 * TimerDriverTestHelper.h
 *
 *  Created on: Aug 24, 2024
 *      Author: root
 */

#ifndef TIMERDRIVERTESTHELPER_H_
#define TIMERDRIVERTESTHELPER_H_

#include <stdint.h>
#include <TIMER_Driver.h>

uint32_t getTimerARRValue (timer_device device);
uint32_t getTimerPSCValue (timer_device device);
uint32_t getTimerCCR1Value (timer_device device);
uint32_t getTimerCCR2Value (timer_device device);
uint32_t getTimerCCMR1Value (timer_device device);
uint32_t getTimerCCMR2Value (timer_device device);
uint32_t getTimerCCERValue (timer_device device);
uint32_t getTimerDIERValue (timer_device device);
uint32_t getTimerEGRValue (timer_device device);
uint32_t getTimerCR1Value (timer_device device);
uint32_t getTimerORValue (timer_device device);
uint32_t getTimerSMCRValue (timer_device device);

#endif /* TIMERDRIVERTESTHELPER_H_ */
