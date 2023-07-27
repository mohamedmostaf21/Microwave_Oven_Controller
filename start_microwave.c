/****************************************************
*  @file    start_microiwave.c
*
*  Start microiwave 
*
*  @author   Mohamed Mostafa Elnahas
*
****************************************************/
#include "stdint.h"
#include "stdlib.h"
#include "tm4c123gh6pm.h"
#include "LCD.h"
#include "LEDs.h"
//function to start the cooking of microwave
void Start_Cooking(char time_sec){
	int i;
	LCD_command(shiftCursorRight);      			//direction of cursor to right
	LCD_command(cursorBlink);         			//turn on display mode and cursor blinking
	LCD_command(clearDisplay) ;       			//clear whatever is written on display 
	RGB_Output(RED+BLUE+GREEN);				//turn on all leds
	Start_Timer(time_sec);					//start counting down	
	for(i = 0; i < 3; i++)
	{
		Buzzer_Output(BuzzerON);			//turn on buzzer
		RGB_Output(OFF);				//turn off leds
		genericDelay_Wait1ms(1000);			//wait 1 sec
		RGB_Output(RED+BLUE+GREEN);			//turn on all leds
		genericDelay_Wait1ms(1000);			//wait 1 sec
	}
	Buzzer_Output(OFF);					//turn off buzzer
	RGB_Output(OFF);
	}

//function to enter no. of kilo of the beef of chicken
void Enter_kilo(char s)
{
	short c;						//variable to represent symbol pressed on keypad
	short check = 1;		//variable used to check and exit while loop
	//while loop to enter no. of kilo and check if number entered is valid or not
	while (check)
	{
		c = 0;
		if (s == 'B')								//check if the food entered is beef
			LCD_Write("Beef Weight?");	//write "Beef Weight? on lcd
		else if (s == 'C')					//check if the food entered is chicken
			LCD_Write("Chicken Weight?");		//write "Chicken Weight? on lcd
		//wait for the user to enter the number if kilo
		while (c == 0)
		{
			c = keypad_getkey();	//c => symbol pressed
		}
		//check if the symbol entered is a number between 1 to 9 or not
		if (c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == '#' || c == '0' || c == '*')
		{
			LCD_Write("Err...");			//write "Err.." on lcd
			genericDelay_Wait1ms(2000);			//wait 2 sec
		}
		//check if the symbol entered is a number between 1 to 9 or not
		else if(c > 0)
		{
			if (s == 'B')						//check if the food entered is beef
				Start_Cooking(30 * c); //Beef is defrosted at a rate of 0.5 minutes per kilo.
			else if (s == 'C')			//check if the food entered is chicken
				Start_Cooking(12 * c); //Chicken is defrosted at a rate of 0.2 minutes per kilo.
			check = 0;							//exit while loop
		}
	}
}

void Cooking_time(void)
{
	short i;	//variable for outer loop
	short j;	//variable for inner loop
	short time_sec;	//total time in sec
	short c = 0;	//variable to represent symbol pressed on keypad
	short flag1 = 1;	//a flag to check if time entered is valid or not
	short flag2 = 1;	//a flag to check is SW2 is pressed or not
	short times[4] = {0,0,0,0};	//an array representing time in 00:00
	short size = sizeof(times) / sizeof(short);	//a variable to determine size of array
	while(flag1)
	{
		flag2 = 1;		//set flag2 to 1
		//a loop to set time to zero
		for(i=0;i<size;i++)
		{
			times[i] = 0;
		}
		Write_Timer(times[3], times[2], times[1], times[0]); //write timer on lcd
		genericDelay_Wait1ms(500);	//wait

		//a loop to let user enter time
		for(i=0; i<size && flag2; i++)
		{
			c = 0;
			//wait for the user to enter the number
			while(c == 0)
			{
				c = keypad_getkey();	//c => symbol pressed
				//check if the symbol entered is a number or not
				if (c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == '#' || c == '*')
				{
					LCD_Write("Err..");			//write "Err.." on lcd
					genericDelay_Wait1ms(2000);			//wait 2 sec
					c = 0;
					Write_Timer(times[3], times[2], times[1], times[0]); //write timer on lcd
					genericDelay_Wait1ms(500);	//wait
				}
				//check if the user pressed start button or not
				if (!SW2_Input())
				{
					flag2 = 0;	//user pressed start button
					break;			//exit from loop
				}
			}
			//check if the user pressed start button or not
			if (flag2)
			{
				//if user pressed c is set to '0' not 0, so if user pressed '0' in this case let c => 0
				if (c == '0')
					c = 0;
				//a  loop to set timer values
				for(j=(size-1);j>=0;j--)
				{
					if(j==0)
						times[j] = c;
					else
						times[j] = times[j-1];
				}
				Write_Timer(times[3], times[2], times[1], times[0]); //write timer on lcd
				genericDelay_Wait1ms(500);	//wait
			}
		}
		time_sec = ((times[3]*10) + times[2])*60 + ((times[1]*10) + times[0]);	//calculate total no. of seconds
		// if time is more than 30 minutes
		if (time_sec > 1800)
		{
			LCD_Write("Max Time is 30");	//write "Max Time is 30" on lcd
			genericDelay_Wait1ms(2000);						//wait 2 sec
		}
		//if time is 00
		else if(time_sec == 0)
		{
			LCD_Write("Time is 0???");	//write	"Time is 0???" on lcd
			genericDelay_Wait1ms(2000);					//wait 2 sec
		}
		else
		{
			while (SW2_Input()){}		//wait for user to press start button
			Start_Cooking(time_sec);	//start cooking
			flag1 = 0;	//exit loop
		}
	}
}
