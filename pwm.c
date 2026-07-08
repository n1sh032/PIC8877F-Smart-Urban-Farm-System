#include <xc.h>
#include "config.h"

void initSysPWM(void)
{
    CCPTMRS1 = 0b00000000;
    PWM6CON = 0b00000000;
    T2PR = 124;
    PWM6DCH = 0b00110010;
    PWM6DCL = 0b00000000;
    T2CLKCON = 0b00000001;
    T2CON = 0b11110000;
    RD2PPS = 0x0E;
    PWM6CON = 0b10000000;
}