/****************************************************
*  @file    LCD.c
*
*  LCD interfacing from scratch Using 4 bit methodology
*
*  @author  Mohamed Mostafa Shaban
*
****************************************************/
#include "LCD.h"
#include "tm4c123gh6pm.h"
#include "SystickTimer.h"
#include <stdint.h>
#include "LEDs.h"

/*
    VSS -> gnd
    VDD -> 5V
    V0  -> Pot
    Rs  -> PA5
    R/W -> gnd
    E   -> PA6
    DB0 -> not connected
    DB1 -> not connected
    DB2 -> not connected
    DB3 -> not connected
    DB4 -> PB4
    DB5 -> PB5
    DB6 -> PB6
    DB7 -> PB7
    A   -> 5V
    K   -> gnd
*/

// we set RS to 1 to write data to DDRAM
// SysTick must be initialized first

void LCD_Init(void)
{
    // Initalize Port B as digital output
    SYSCTL_RCGCGPIO_R |= 0x02;
    while ((SYSCTL_PRGPIO_R & 0x02) == 0) {}
    GPIO_PORTB_LOCK_R = 0x4C4F434B;
    GPIO_PORTB_PCTL_R = 0;
    GPIO_PORTB_CR_R  |= 0xFF;
    GPIO_PORTB_DIR_R |= 0xFF;
    GPIO_PORTB_DEN_R |= 0xFF;
    GPIO_PORTB_AMSEL_R = 0x00;
    GPIO_PORTB_PUR_R = 0;
    // initialize port A
    SYSCTL_RCGCGPIO_R |= 0x01;
    while ((SYSCTL_PRGPIO_R & 0x01) == 0) {}
    GPIO_PORTA_PCTL_R = 0;
    GPIO_PORTA_CR_R  |= 0x60;
    GPIO_PORTA_DIR_R |= 0x60;
    GPIO_PORTA_DEN_R |= 0x60;
    GPIO_PORTA_AMSEL_R = 0x00;
    GPIO_PORTA_PUR_R = 0;
    // LCD initialization from datasheet
    genericDelay_Wait1ms(15);
    LCD_command(0x30);
    genericDelay_Wait1ms(5);
    LCD_command(0x30);
    genericDelay_Wait1us(100);
    LCD_command(0x30);
    LCD_command(0x20);
    LCD_command(setTo4Bits);
    LCD_command(entryMode);
		LCD_command(cursorBlink);
    genericDelay_Wait1ms(2);
}

void LCD_print4bits(char dataInput, char ctrl)
{
	dataInput &= 0xF0;   //select  that the MSB of data (D7 D6 D5 D4)
	ctrl &= 0xF0;  //check that the 4 MSB are (D7 D6 D5 D4) only
	GPIO_PORTB_DATA_R = dataInput;
	GPIO_PORTA_DATA_R |= ctrl;
	GPIO_PORTA_DATA_R |= ctrl | EN; //secure Enable
	genericDelay_Wait1us(0);
	GPIO_PORTA_DATA_R &= ~0x60;
	GPIO_PORTB_DATA_R = 0;
}

void LCD_command(char command)
{
    LCD_print4bits(command & 0xF0, 0); // write MSB 4 bits of command
    LCD_print4bits(command << 4, 0);   // write LSB 4 bits of control
  if ((command == clearDisplay) || (command == returnHome)) // they take longer time
       genericDelay_Wait1ms(2);
    else
        genericDelay_Wait1us(40);
}

// for sending characters
void LCD_data(char dataInput)
{
    LCD_print4bits(dataInput & 0xF0, RS);    // send MSB 4 bits, and set RS
    LCD_print4bits(dataInput << 4, RS);      // send LSB 4 bits, and set RS
    genericDelay_Wait1us(40);
}
//To send string directly
void LCD_sendString(char* str)
{
  uint32_t i = 0;
  while (str[i] != '\0')
  {
    LCD_data(str[i]);
    i++;
  }
}
//Using the function for print any string on lcd
void LCD_Write(char *str)    //Function to write on LCD
{
	LCD_command(cursorBlink);
	LCD_command(clearDisplay);    //clear whatever is written on display
	genericDelay_Wait1ms(500);
	LCD_sendString(str);
	genericDelay_Wait1ms(500);
}
