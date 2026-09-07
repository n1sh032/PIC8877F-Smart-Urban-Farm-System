#include <xc.h>
#include "config.h"

#define LCD_DATA_D7 PORTDbits.RD7
#define LCD_DATA_D6 PORTDbits.RD6
#define LCD_DATA_D5 PORTDbits.RD5
#define LCD_DATA_D4 PORTDbits.RD4
#define LCD_RS      PORTEbits.RE1
#define LCD_E       PORTEbits.RE0

void lcdWriteNibble(unsigned char nibble)
{
    LCD_DATA_D7 = (nibble & 0b00001000) >> 3;
    LCD_DATA_D6 = (nibble & 0b00000100) >> 2;
    LCD_DATA_D5 = (nibble & 0b00000010) >> 1;
    LCD_DATA_D4 = (nibble & 0b00000001);

    LCD_E = 1;
    __delay_ms(1);
    LCD_E = 0;
    __delay_ms(1);
}

void lcdWriteCtrlWord(unsigned char x)
{
    unsigned char upper_nibble, lower_nibble;
    upper_nibble = (x & 0b11110000) >> 4;
    lower_nibble = x & 0b00001111;

    LCD_RS = 0;
    lcdWriteNibble(upper_nibble);
    lcdWriteNibble(lower_nibble);
}

void lcdWriteDspData(unsigned char x)
{
    unsigned char upper_nibble, lower_nibble;
    upper_nibble = (x & 0b11110000) >> 4;
    lower_nibble = x & 0b00001111;

    LCD_RS = 1;
    lcdWriteNibble(upper_nibble);
    lcdWriteNibble(lower_nibble);
}

void lcdCtrl_FunctionSet(void)
{
    lcdWriteCtrlWord(0b00101000);   // 4-bit, 2 lines, 5x7
}

void lcdCtrl_OnOffDisplay(unsigned char display_state, unsigned char cursor_state)
{
    unsigned char pattern = 0b00001000;
    if(display_state == 1) pattern |= 0b00000100;
    if(cursor_state == 1)  pattern |= 0b00000011;
    lcdWriteCtrlWord(pattern);
}

void lcdCtrl_SetEntryMode(void)
{
    lcdWriteCtrlWord(0b00000110);
}

void lcdCtrl_ClearDisplay(void)
{
    lcdWriteCtrlWord(0b00000001);
}

void lcdCtrl_SetPos(unsigned char row, unsigned char col)
{
    unsigned char ramAddr;
    if (row == 1)
        ramAddr = col - 1;
    else
        ramAddr = 0x40 + col - 1;
    lcdWriteCtrlWord(0x80 + ramAddr);
}

void initLCD(void)
{
    __delay_ms(15);
    lcdWriteCtrlWord(0b00000011);
    __delay_ms(5);
    lcdWriteCtrlWord(0b00000010);

    lcdCtrl_FunctionSet();
    lcdCtrl_OnOffDisplay(1, 0);
    lcdCtrl_SetEntryMode();
    lcdCtrl_ClearDisplay();
}

void lcdWriteString(const char *str)
{
    while(*str != 0)
    {
        lcdWriteDspData(*str);
        str++;
    }
}
