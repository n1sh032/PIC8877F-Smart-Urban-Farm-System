#include <xc.h>
#include "config.h"

volatile unsigned char displayMode = 0;

extern volatile unsigned int adc_RawResult;
extern volatile unsigned char adc_ConvDoneFlag;

void __interrupt() ISR(void)
{
    if(INTF == 1)
    {
        displayMode++;

        if(displayMode > 2)
        {
            displayMode = 0;
        }
        INTF = 0;
    }

    if(PIR1bits.ADIF == 1)
    {
        PIR1bits.ADIF = 0;
        adc_RawResult = ADRESH*256 + ADRESL;
        adc_ConvDoneFlag = 1;
    }
}
