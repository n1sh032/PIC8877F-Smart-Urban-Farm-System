#include <xc.h>
#include "config.h"

void initPWM(void)
{
    
    CCPTMRS1 = 0b00000100;    // PWM6 uses Timer2

    PWM6CON = 0b00000000;     // Disable PWM during setup

    T2PR = 124;               // Sets PWM period

    T2CON = 0b11110000;       // Timer2 ON, prescaler 1:128, postscaler 1:1

    T2CLKCON = 0b00000001;    // Timer2 clock source = FOSC/4

    RD3PPS = 0x0E;            // PWM6 output connected to RB5

    PWM6CONbits.EN = 1;       // Enable PWM6
}
void pwm25(void)
{
    // 25% Duty Cycle
    // PWM6DC = 500 x 25% = 125
    // 125 = 00 0111 1101

    PWM6DCH = 0b00011111;
    PWM6DCL = 0b01000000;
}

void pwm50(void)
{
    
//50% Duty Cycle
//PWM6DC = 200 x (50/40) = 250
//0b0011111010
//PWM6DCH = 00111110
//PWM6DCL = 10000000
     

    PWM6DCH = 0b00111110;
    PWM6DCL = 0b10000000;
}


void pwm100(void)
{
//100% Duty Cycle
//PWM6DC = 200 x (100/40) = 500
//0b0111110100
//PWM6DCH = 01111101
//PWM6DCL = 00000000
     

    PWM6DCH = 0b01111101;
    PWM6DCL = 0b00000000;
}
   
//      PWM Calculation
//     
//      FOSC = 4MHz
//     
//      TOSC = 1 / FOSC
//           = 1 / 4MHz
//          = 0.25us
//     
//      Tcy = 4 x TOSC
//          = 1us
//     
//      Timer2 Prescaler = 1:128
//     
//      T2PR = 124
//     
//      Timer2 Count
//      = T2PR + 1
//      = 124 + 1
//      = 125
//     
//      PWM Period
//      = Count x Tcy x Prescaler
//      = 125 x 1us x 128
//      = 16000us
//      = 16ms
//     
//      PWM Frequency
//      = 1 / PWM Period
//      = 1 / 0.016
//      = 62.5Hz
//     
//      Postscaler = 1:1
//      (Postscaler does not affect PWM frequency)
