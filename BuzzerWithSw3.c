/****************************************************
*  @file    BuzzerWithSW3.c
*
*
*  @author   Mohamed Mostafa Elnahas
*
*
****************************************************/
#include "stdint.h"
#include "stdlib.h"
#include "tm4c123gh6pm.h"
/* Hardware Connections
		Sw3 => Pin A3
		Buzzer => Pin A2
*/
void SW3WithBuzzer_Init(void)
{

	SYSCTL_RCGCGPIO_R |= 0x01;           							//activate clock for PORTA
  while((SYSCTL_PRGPIO_R & 0x01)==0){}           		//Check if PORTA is activated or not
	GPIO_PORTA_LOCK_R = 0x4C4F434B;           				//unlock GPIO of PORTA
	GPIO_PORTA_CR_R |= 0x0C;                   				//Enable GPIOPUR register enable to commit
	GPIO_PORTA_PUR_R |= 0x08;   											//Enable Pull Up SW on PA3
  GPIO_PORTA_DEN_R |= 0x04;        	  							//Digital Enable A2 of PORTA
	GPIO_PORTA_DEN_R |= 0x08;        	  							//Digital Enable A3 of PORTA
  GPIO_PORTA_DIR_R |= 0x04;        	  							//Make A2 of PORTA as ouptut pin
	GPIO_PORTA_PCTL_R &=~ 0x00000F00; 											//Regular GPIO of PORTA
  GPIO_PORTA_AMSEL_R &=~ 0x04;        							//Disable analog function on A2 of PORTA
	GPIO_PORTA_AFSEL_R &=~ 0x04;        							//Disable alternate function on A2 of PORTA
	GPIO_PORTA_PCTL_R &=~ 0x08 ; 											// Regular GPIO of PORTA
  GPIO_PORTA_AMSEL_R &=~ 0x08;        							//Disable analog function on A3 of PORTA
	GPIO_PORTA_AFSEL_R &=~ 0x08;        							//Disable alternate function on A3 of PORTA


    //Interrupt for switch 3
  GPIO_PORTA_IS_R &= ~0x04;                 // PA4 is low level event
  GPIO_PORTA_IEV_R &= ~0x00;               // PA4 level event
  GPIO_PORTA_ICR_R = 0x04;                // clear flag4
  GPIO_PORTA_IM_R |= 0x04;               // arm interrupt on PA4 
  NVIC_PRI0_R = ((NVIC_PRI0_R&0xFF00FFFF)|0x00000000 ); // priority 5 of port f 
  NVIC_EN0_R = 0x00000001;             //  enable interrupt of port A
  __enable_irq();                     // Enable global Interrupt 
	
}
//Check if SW3 is pressed or not
unsigned char SW3_Input(void)
{
  return (GPIO_PORTA_DATA_R & 0x08);
}

//Turn ON, Turn OFF Buzzer
void Buzzer_Output(unsigned char data)
{
  GPIO_PORTA_DATA_R = (GPIO_PORTA_DATA_R & 0x0B) + data;
}
