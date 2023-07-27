/**************************************************
*  @file    LEDs.c
*
*  LEDs,Switches interface for better user experience.
*
*  @author   Youssef Eslam
*
**************************************************/
#include "stdint.h"
#include "stdlib.h"
#include "tm4c123gh6pm.h"
#include "LCD.h"
void EnableInterrupts(void);
uint8_t Counter=0;
uint32_t RGB_color [8] ={0x00,0x02,0x04,0x06,0x08,0x0A,0x0C,0x0E};

//Intilization of PORTF
void PortFInit(void)
{
	SYSCTL_RCGCGPIO_R |= 0x20;
	while((SYSCTL_PRGPIO_R & 0x20)==0){}
	GPIO_PORTF_LOCK_R = 0x4C4F434B;
	GPIO_PORTF_CR_R |= 0x1F;
	GPIO_PORTF_AMSEL_R &=~ 0x1F;
	GPIO_PORTF_PCTL_R &=~ 0x000FFFFF;
	GPIO_PORTF_DIR_R &=~ 0x11;
	GPIO_PORTF_DIR_R |= 0x0E;
	GPIO_PORTF_AFSEL_R &=~ 0x1F;
	GPIO_PORTF_DEN_R |= 0x1F;
	GPIO_PORTF_PUR_R |= 0x11;
}

//
void SW2_Interrupt(void)
{
		// negative edge triggered (falling ) configuration
	GPIO_PORTF_IS_R &= ~0x10;
	GPIO_PORTF_IBE_R &= ~0x10;
	GPIO_PORTF_IEV_R &= ~0x10;
	// configuration to enable interrupts
	//arm interrupt portf pin4 (switch)
	GPIO_PORTF_IM_R |= 0x10;
	//enable interrupts
	//EnableInterrupts();
	//enable IRQ from port f ( IRQ 30 > EN0 bit 30)
	NVIC_EN0_R |= (1 << 30); // EN0 bit 30
	//Setting portf priority (use any method of the following lines )
	NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00400000 ;
	NVIC_PRI7_R = (NVIC_PRI7_R & 0xFF00FFFF) | (2 << 21);
	NVIC_PRI7_R = (NVIC_PRI7_R & 0xFF00FFFF) | (1 << 22);
}

//Check if SW1 in TivaC is pressed or not
unsigned char SW1_Input(void)
{
	return GPIO_PORTF_DATA_R & 0x10;
}

//Check if SW2 in TivaC is pressed or not
unsigned char SW2_Input(void)
{
	return GPIO_PORTF_DATA_R & 0x01;
}

//Check if SW1 and SW2 is pressed or not
unsigned char SW_Input(void)
{
	return GPIO_PORTF_DATA_R & 0x11;
}


//Turn ON, Turn OFF, Change Color of LEDS in TivaC
void RGB_Output(unsigned char data)
{
	GPIO_PORTF_DATA_R = (GPIO_PORTF_DATA_R & 0x11) + 0x00;
	GPIO_PORTF_DATA_R = (GPIO_PORTF_DATA_R & 0x11) + data;
}

/*void GPIOF_Handler(void)
{
	GPIO_PORTF_ICR_R |=0x10;
	GPIO_PORTF_DATA_R =RGB_color [Counter];
	Counter++;
	if (Counter ==8) Counter=0;
}*/
