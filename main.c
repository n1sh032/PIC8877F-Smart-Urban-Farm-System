#include <xc.h>
#include "config.h"

void initSysPins(void);
void initSysPWM(void);
void motor_On(void);
void motor_Off(void);

void main(void)
{
    initSysPins();
    initSysPWM();

    while(1)
    {
        motor_On();
        __delay_ms(3000);

        motor_Off();
        __delay_ms(3000);
    }
}

void initSysPins(void)
{
    ANSELA = 0b00000000;
    ANSELB = 0b00000000;
    ANSELD = 0b00000000;

    TRISA = 0b11110111;
    TRISD = 0b11111000;
}