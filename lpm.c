#include <xc.h>
#include "config.h"

void fanOff(void);
void pumpOff(void);

void adc_StartConversion(unsigned char channel);

void lcdCtrl_ClearDisplay(void);
void lcdCtrl_SetPos(unsigned char row, unsigned char col);
void lcdWriteString(const char *str);

unsigned char lpmMode = 0;

void initLPM(void)
{
    TRISBbits.TRISB2 = 1;
    IOCBPbits.IOCBP2 = 1;  
    IOCIE = 1;            
    GIE = 1;
}

unsigned char lpm_CheckSwitch(void)
{
    if(PORTBbits.RB2 == 1)
    {
        __delay_ms(50);

        if(PORTBbits.RB2 == 1)
        {
            lpmMode = !lpmMode;
            while(PORTBbits.RB2 == 1);
        }
    }

    return lpmMode;
}

void lpm_Enter(void)
{
    fanOff();
    pumpOff();
    PORTAbits.RA1 = 0;
    PORTAbits.RA0 = 0;   

    lcdCtrl_ClearDisplay();
    lcdCtrl_SetPos(1, 1);
    lcdWriteString("Low Power Mode");
    lcdCtrl_SetPos(2, 1);
    lcdWriteString("Activated");
    __delay_ms(500);

    SLEEP();
    NOP();

    while(PORTBbits.RB2 == 1);   

    lpmMode = 0;
    PORTAbits.RA0 = 0;

    lcdCtrl_ClearDisplay();
    lcdCtrl_SetPos(1, 1);
    lcdWriteString("Resuming...");
    __delay_ms(300);

    adc_StartConversion(0b00100010);     
}
