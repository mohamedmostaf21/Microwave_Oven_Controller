/*******************************************************
*  @file   SystickTimer.h
*
*  Systick Timer With PLL to run at 80 MHZ clock Frequency
*
*  @author  Mohamed Mostafa Shaban
*
*******************************************************/

#ifndef SYSTICKTIMER_H_INCLUDED
#define SYSTICKTIMER_H_INCLUDED
#include "tm4c123gh6pm.h"
#include <stdint.h>
// Functions definitions of SysTick
void SysTick_Init(void);
void SysTick_Wait(uint32_t delay);
void genericDelay_Wait1ms(uint32_t delayms);
void genericDelay_Wait1us(uint32_t delayus);
void PLL_Init(void);

#endif
// SYSTICKTIMER_H_INCLUDED

