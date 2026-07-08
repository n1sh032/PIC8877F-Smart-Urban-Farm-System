#include <xc.h>
#include "config.h"

void motor_On(void)
{
    PORTDbits.RD0 = 1;       // IN1
    PORTDbits.RD1 = 0;       // IN2
    PWM6CONbits.EN = 1;      // Enable PWM output on RD2
}

void motor_Off(void)
{
    PWM6CONbits.EN = 0;      // Disable PWM
    PORTDbits.RD0 = 0;
    PORTDbits.RD1 = 0;
    PORTDbits.RD2 = 0;
}