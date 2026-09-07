#include <xc.h>
#include "config.h"

void lcdCtrl_SetPos(unsigned char row, unsigned char col);
void lcdWriteString(const char *str);
void lcdCtrl_ClearDisplay(void);
void lcdWriteDspData(unsigned char x);

void dspTask_OnLCD(unsigned char mode, unsigned int value)
{
    char numStr[6];
    unsigned int thousands, hundreds, tens, ones;

    lcdCtrl_ClearDisplay();
    lcdCtrl_SetPos(1, 1);

    if(mode == 0)
        lcdWriteString("Temp:");
    else if(mode == 1)
        lcdWriteString("Moisture:");
    else
        lcdWriteString("Light:");

    thousands = (value / 1000) % 10;
    hundreds  = (value / 100) % 10;
    tens      = (value / 10) % 10;
    ones      = value % 10;

    lcdCtrl_SetPos(2, 1);
    if(value >= 1000) lcdWriteDspData(thousands + '0');
    if(value >= 100)  lcdWriteDspData(hundreds + '0');
    if(value >= 10)   lcdWriteDspData(tens + '0');
    lcdWriteDspData(ones + '0');
}
