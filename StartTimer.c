/****************************************************
*  @file    StartTimer.c
*
*  Timer Functions
*
*  @author   Moaz Mohamed
****************************************************/
#include "stdint.h"
#include "stdlib.h"
#include "tm4c123gh6pm.h"
#include "LCD.h"
#include "LEDs.h"

//function to start count down of timer and know number of minutes and seconds
volatile unsigned int flag = 1;
void flag_stop(void){
	flag =0;
}
short time_4;
short time_3;
short time_2;
short time_1;
//function to start count down of timer and know number of minutes and seconds
void Start_Timer(short time_sec){
	flag =1;
	//short time_4;
	time_4 = (time_sec/60)/10;									//(0)0:00
	//short time_3;
	time_3 = (time_sec/60)-(time_4 *10);	//0(0):00
	//short time_2;
	time_2 = (time_sec/10)-6*(time_3+time_4*10);		//00:(0)0
	//short time_1;
	time_1 = time_sec-(time_2*10+(time_4*10+time_3)*60);	//00:0(0)
	Write_Timer(time_4 ,time_3 ,time_2 ,time_1);
	genericDelay_Wait1ms(1000);	
	while(time_4 | time_3 | time_2 | time_1 ){
		if(time_1!=0){
				time_1 = time_1 -1;
				Write_Timer(time_4,time_3,time_2,time_1);		
				genericDelay_Wait1ms(1000);	
			}
		else if (time_2 !=0 && time_1 ==0){
				time_2 = time_2 - 1;
				time_1 = 9;
				Write_Timer(time_4,time_3,time_2,time_1);		
				genericDelay_Wait1ms(1000);	
			}
		else if (time_3!=0 && time_2 ==0 && time_1 ==0){
		
				time_3 = time_3-1;
				time_2=5;
				time_1=9;		
				Write_Timer(time_4,time_3,time_2,time_1);		
				genericDelay_Wait1ms(1000);	
			}
		else if (time_4!=0 && time_3==0 && time_2 ==0 && time_1 ==0){
				time_4 = time_4 -1;
				time_3 = 9;
				time_2=5;
				time_1=9;		
				Write_Timer(time_4,time_3,time_2,time_1);		
				genericDelay_Wait1ms(1000);	
			}
		else if (flag == 0)
		{
			time_4 = 0;
			time_3 = 0;
			time_2 = 0;
			time_1 = 0;
		}
	}
}
//function to write timer on lcd
void Write_Timer(short time4, short time3, short time2, short time1)
{
	LCD_command(shiftCursorRight);      //direction of cursor to right
	LCD_command(clearDisplay);        //clear whatever is written on display
	LCD_data(time4 + '0');					//(0)0:00
	LCD_data(time3 + '0');					//0(0):00
	LCD_data(':');						//00(:)00
	LCD_data(time2 + '0');					//00:(0)0
	LCD_data(time1 + '0');					//00:0(0)
}
