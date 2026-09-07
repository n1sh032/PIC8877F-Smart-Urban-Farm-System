#include <xc.h>
#include "config.h"

unsigned int adc_RawResult;
unsigned char adc_ConvDoneFlag = 0;

void initADC(void)
{
    ADREF = 0b00000000;
    ADCLK = 0b00000011;
    ADACQ = 0b00000000;
    ADCON0 = 0b10000100;

    PIR1bits.ADIF = 0;
    PIE1bits.ADIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}

void adc_StartConversion(unsigned char channel)
{
    ADPCH = channel;
    __delay_us(5);
    adc_ConvDoneFlag = 0;
    ADCON0bits.ADGO = 1;
}

unsigned int adc_ToTemperature(unsigned int adcResult)
{
    unsigned int temp_int;
    float voltage;
    float temp;

    voltage = adcResult * (4.9763 / 1023);
    temp = (voltage - 0.4) / 0.0195;
    temp_int = (unsigned int)(temp + 0.5);

    return temp_int;
}

unsigned int adc_ToMoisture(unsigned int adcResult)
{
    unsigned int moisturePercent;

    moisturePercent =
    (unsigned int)(100 - ((adcResult * 100.0) / 1023));

    return moisturePercent;
}

unsigned int adc_ToLight(unsigned int adcResult)
{
    unsigned int lightPercent;

    lightPercent =
            (unsigned int)((adcResult * 100.0) / 1023);

    return lightPercent;
}
