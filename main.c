#include "stdint.h"
#include "stdlib.h"
#include "tm4c123gh6pm.h"
#include "LCD.h"
#include "LEDs.h"
//some shortCuts  used in main function
#define OFF           			0x00
#define BuzzerON            		0x04
#define RED 				0x02
#define BLUE 				0x04
#define GREEN 				0x08
#define IDLE				0
#define POPCORN				1
#define BEEF				2
#define CHICKEN				3
#define COOKINGTIME			4

void SystemInit(){}

int main(void)
{
	short c;
	int state = IDLE;
	PortFInit();				
 	keypad_Init();
	SW3WithBuzzer_Init();	
	LCD_Init();					
	PLL_Init();
	while (1)
	{
		
		switch(state)
		{
			//IDLE case
			case IDLE :
				c = 0;
				LCD_command(clearDisplay);      	//clear whatever is written on display
				LCD_command(cursorBlink);           	//turn on display mode and cursor blinking
				genericDelay_Wait1ms(500);
				RGB_Output(OFF);
				c = keypad_getkey();
				if (c == 'A')
					state = POPCORN;
				else if (c == 'B')
					state = BEEF;
				else if (c == 'C')
					state = CHICKEN;
				else if(c == 'D')
					state = COOKINGTIME;
				break;

			//check POP CORN case
			case POPCORN :
				RGB_Output(BLUE + GREEN);
				LCD_Write("POP CORN");
				while(SW2_Input()){}
				Start_Cooking(60);
				state = IDLE;
				break;

			//check BEEF case
			case BEEF :
				RGB_Output(BLUE);
				Enter_kilo('B');
				state = IDLE;
				break;
				
			//check CHICKEN case
			case CHICKEN :
				RGB_Output(GREEN);
				Enter_kilo('C');
				state = IDLE;
				break;	
             		//COOKING case
			case COOKINGTIME :
				RGB_Output(GREEN + RED);
				LCD_Write("Cooking Time");
				Cooking_time();
				state = IDLE;
				break

		}
	}
}
