#include <xc.h>
#include "config.h"



void pumpOn(void)
{
    PORTDbits.RD0 = 1;
}

void pumpOff(void)
{
    PORTDbits.RD0 = 0;
}


void fanOn(void)
{
    PORTDbits.RD1 = 1;
}

void fanOff(void)
{
    PORTDbits.RD1 = 0;
}
