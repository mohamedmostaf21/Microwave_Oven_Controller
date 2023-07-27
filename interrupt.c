/****************************************************
*  @file    interrupt.c
*
*
*  @author   all group
*
*
****************************************************/
#include "stdint.h"
#include "stdlib.h"
#include "tm4c123gh6pm.h"
#include "LEDs.h"

int flag1 =1;
void GPIOF_Handler(void){
	int i;
	flag1 = 1;
	while(!SW1_Input()){};				//pause
		RGB_Output(RED+BLUE+GREEN);
		while(flag1){
			GPIO_PORTF_DATA_R ^= RED+GREEN+BLUE;
			for(i=0;i<300000 && flag1;i++) 			//for delay because systick wait is an interrupt
			{
				if(!SW2_Input()){
					while(!SW2_Input()){}
				GPIO_PORTF_ICR_R |= 0x10;
				RGB_Output(RED+BLUE+GREEN);
				flag1 = 0;
				break;
					}
			else if(!SW1_Input())
			{
				while(!SW1_Input()){}
				flag_stop();
				RGB_Output(RED+BLUE+GREEN);
				flag1 = 0;
				break;
			}	
		}
	}
GPIO_PORTF_ICR_R |= 0x10;
}

void GPIOA_Handler(void){
 GPIO_PORTA_ICR_R |= 0x04; // acknowledge flag4 of pin 4
 while(SW3_Input()==0){
 }
}
