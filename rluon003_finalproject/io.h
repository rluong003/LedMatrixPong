#ifndef __io_h__
#define __io_h__

void LCD_init();
void LCD_WriteData(unsigned char Data);
void LCD_ClearScreen(void);
void LCD_WriteCommand (unsigned char Command);
void LCD_Cursor (unsigned char column);
void LCD_DisplayString(unsigned char column ,  char *string);
void delay_ms(int miliSec);
#endif
