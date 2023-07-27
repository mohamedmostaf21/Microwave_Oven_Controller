/****************************************************
*  @file    LCD.h
*
*  LCD library to send both commands and data to an LCD.
*  generalized library could be used in diffrent types of LCDs.
*
*  @author  Mohamed Mostafa Shaban
*
****************************************************/
/*  @Hardware Connentions
*
*  [PB4 - PB7] ->   [BD4 - BD7]   I/O Data Bus.
*  PA5         ->   RS            Register Select.
*  GND         ->   RW            Read / Write Register.
*  PA6         ->   E             Enable Pin.
*
****************************************************/
/*define useful symbolic names for LCD commands */
#define EN                  0x40    // PB0
#define RS                  0x20    // PB5
#define clearDisplay        0x01    // delay 2ms
// writes blank to all addresses and returns to address 0
#define returnHome          0x02    // delay 2ms
// returns to address 0 and to original state
// cursor goes to left edge of first line
#define displayOn           0x0A    // delay 37us
// should be on to display the characters
#define cursorOn            0x0E    // delay 37us
// displays cursor position
#define cursorBlink         0x0F    // delay 37us
// blinks cursor or character at which cursor is
#define shiftCursorRight    0x06    // delay 37us
#define shiftCursorLeft     0x08    // delay 37us
// in 2-line display, it moves to second line when passes 40
#define setTo4Bits          0x28    // delay 37us
// 4-bit length, 2 display lines, 5x8 font
#define entryMode           0x06    // delay 37us
// increments DDRAM address by 1 when a character is written into it
#define nextLine						0xC0


// we set RS to 1 to write data
void LCD_Init(void);
void LCD_print4bits(char dataInput, char ctrl);
void LCD_command(char command);
void LCD_data(char dataInput);
void LCD_sendString(char* str);
void LCD_errormsg(void);
void LCD_Write(char *str);
