#include <xc.h>
#include "config.h"

void initSysPins(void);

void main(void)
{
    initSysPins();

    while(1)
    {
        // Motor Forward
        PORTDbits.RD0 = 1;
        PORTDbits.RD1 = 0;
        __delay_ms(3000);

        // Stop
        PORTDbits.RD0 = 0;
        PORTDbits.RD1 = 0;
        __delay_ms(3000);

        // Motor Reverse
        PORTDbits.RD0 = 0;
        PORTDbits.RD1 = 1;
        __delay_ms(3000);

        // Stop
        PORTDbits.RD0 = 0;
        PORTDbits.RD1 = 0;
        __delay_ms(3000);
    }
}

void initSysPins(void)
{
    ANSELA = 0b00000000;
    ANSELB = 0b00000000;
    ANSELD = 0b00000000;

    TRISA = 0b11110111;     // RA3 LED output
    TRISD = 0b11111100;     // RD0 and RD1 outputs
}