#include <xc.h>
#include "config.h"

// Functions from other files
void motor_Off(void);

// Override flags
volatile unsigned char fanOverride = 0;
volatile unsigned char pumpOverride = 0;

void initSysExtInt(void)
{
    // RB0 = External Interrupt button

    TRISBbits.TRISB0 = 1;
    ANSELBbits.ANSB0 = 0;

    INTPPS = 0x08;            // Map INT to RB0

    INTCONbits.INTEDG = 0;    // Falling edge interrupt

    PIR0bits.INTF = 0;        // Clear INT flag
    PIE0bits.INTE = 1;        // Enable external interrupt

    INTCONbits.GIE = 1;       // Enable global interrupt
}

void initSysIOC(void)
{
    // RB2 = fan override switch
    // RB3 = pump override switch

    TRISBbits.TRISB2 = 1;
    TRISBbits.TRISB3 = 1;

    ANSELBbits.ANSB2 = 0;
    ANSELBbits.ANSB3 = 0;

    IOCBNbits.IOCBN2 = 1;     // Detect falling edge on RB2
    IOCBNbits.IOCBN3 = 1;     // Detect falling edge on RB3

    IOCBFbits.IOCBF2 = 0;
    IOCBFbits.IOCBF3 = 0;

    PIR0bits.IOCIF = 0;
    PIE0bits.IOCIE = 1;

    INTCONbits.GIE = 1;
}

void __interrupt() isr(void)
{
    // External Interrupt: emergency stop
    if(PIR0bits.INTF == 1)
    {
        motor_Off();

        LATAbits.LATA3 = 1;   // Alert LED ON

        PIR0bits.INTF = 0;    // Clear INT flag
    }

    // IOC on RB2: fan override
    if(IOCBFbits.IOCBF2 == 1)
    {
        fanOverride = ~fanOverride;
        IOCBFbits.IOCBF2 = 0;
    }

    // IOC on RB3: pump override
    if(IOCBFbits.IOCBF3 == 1)
    {
        pumpOverride = ~pumpOverride;
        IOCBFbits.IOCBF3 = 0;
    }

    PIR0bits.IOCIF = 0;
}