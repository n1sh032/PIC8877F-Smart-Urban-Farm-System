#include <xc.h>
#include "config.h"

void initSysUart(void)
{
    TX1STA = 0b00100100;   // TX9=0, TXEN=1, SYNC=0, BRGH=1
    RC1STA = 0b10000000;   // SPEN=1 

    BAUDCON = 0b00001000;  // BRG16=1
    SP1BRGH = 0x00;
    SP1BRGL = 0x67;         // 9600 bps 
}

void eusartWrite(unsigned char txData)
{
    while(TX1STAbits.TRMT == 0);
    TX1REG = txData;
}

void eusartWriteString(const char *str)
{
    while(*str != 0)
    {
        eusartWrite(*str);
        str++;
    }
}

void eusartWriteNumber(unsigned int value)
{
    unsigned int thousands, hundreds, tens, ones;

    thousands = (value / 1000) % 10;
    hundreds  = (value / 100) % 10;
    tens      = (value / 10) % 10;
    ones      = value % 10;

    if(value >= 1000) eusartWrite(thousands + '0');
    if(value >= 100)  eusartWrite(hundreds + '0');
    if(value >= 10)   eusartWrite(tens + '0');
    eusartWrite(ones + '0');
}
