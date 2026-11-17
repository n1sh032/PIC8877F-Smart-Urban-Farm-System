#include <xc.h>

void fanOff(void);
void pumpOff(void);
void lcdCtrl_ClearDisplay(void);
void lcdCtrl_SetPos(unsigned char row, unsigned char col);
void lcdWriteString(const char *str);

void initLPM(void)
{
    TRISBbits.TRISB2 = 1;
}

unsigned char lpm_CheckSwitch(void)
{
    return PORTBbits.RB2;
}

void lpm_Enter(void)
{
    fanOff();
    pumpOff();
    PORTAbits.RA1 = 0;
    PORTAbits.RA0 = 1;
    lcdCtrl_ClearDisplay();
    lcdCtrl_SetPos(1, 1);
    lcdWriteString("Low Power Mode");
}
