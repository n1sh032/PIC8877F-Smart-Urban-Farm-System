#include <xc.h>
#include "config.h"

void initADC(void);
void initEXTINT(void);
void initPWM(void);
void initLCD(void);
void initSysUart(void);
void initLPM(void);

void adc_StartConversion(unsigned char channel);
unsigned int adc_ToTemperature(unsigned int adcResult);
unsigned int adc_ToMoisture(unsigned int adcResult);
unsigned int adc_ToLight(unsigned int adcResult);

void dspTask_OnLCD(unsigned char mode, unsigned int value);
void lcdCtrl_ClearDisplay(void);
void lcdCtrl_SetPos(unsigned char row, unsigned char col);
void lcdWriteString(const char *str);

void eusartWrite(unsigned char txData);
void eusartWriteString(const char *str);
void eusartWriteNumber(unsigned int value);

void fanOn(void);
void fanOff(void);
void pumpOn(void);
void pumpOff(void);
void pwm25(void);
void pwm50(void);
void pwm100(void);

unsigned char lpm_CheckSwitch(void);
void lpm_Enter(void);

extern unsigned char displayMode;
extern unsigned int adc_RawResult;
extern unsigned char adc_ConvDoneFlag;

void initSysPins(void);

void main(void)
{
    unsigned int temp = 0;
    unsigned int moisture = 0;
    unsigned int light = 0;
    unsigned char sensorTurn = 0;
    unsigned char lastDisplayMode = 255;
    unsigned int lastValue = 65535;
    unsigned int currentValue;

    initSysPins();
    initADC();
    initPWM();
    initEXTINT();
    initLCD();
    initSysUart();
    initLPM();

    adc_StartConversion(0b00100010);

    while(1)
    {
        if(lpm_CheckSwitch() == 1)
        {
            lpm_Enter();
        }
        else
        {
            PORTAbits.RA0 = 0;
            if(adc_ConvDoneFlag == 1)
            {
                adc_ConvDoneFlag = 0;

                if(sensorTurn == 0)
                {
                    temp = adc_ToTemperature(adc_RawResult);
                    eusartWriteString("TEMP:");
                    eusartWriteNumber(temp);
                    eusartWriteString("\r\n");
                    sensorTurn = 1;
                    adc_StartConversion(0b00001101);
                }
                else if(sensorTurn == 1)
                {
                    moisture = adc_ToMoisture(adc_RawResult);
                    eusartWriteString("MOISTURE:");
                    eusartWriteNumber(moisture);
                    eusartWriteString("\r\n");
                    sensorTurn = 2;
                    adc_StartConversion(0b00011010);
                }
                else
                {
                    light = adc_ToLight(adc_RawResult);
                    eusartWriteString("LIGHT:");
                    eusartWriteNumber(light);
                    eusartWriteString("\r\n");
                    sensorTurn = 0;
                    adc_StartConversion(0b00100010);
                }
            }

            if(temp < 35)
            {
                fanOff();
            }
            else
            {
                fanOn();
                eusartWriteString("WARNING: Temp high, fan ON\r\n");
            }

            if(moisture < 30)
            {
                
                pumpOn();
                pwm100();
                eusartWriteString("WARNING: Soil dry, pump ON\r\n");
            }
            else if(moisture < 70)
            {
                pumpOn();
                pwm25();
            }
            else if(moisture > 70)
            {
                pumpOff();
            }

            if(light < 40) {
                PORTAbits.RA1 = 1;
            }
            else {
                PORTAbits.RA1 = 0;
            }

            if(displayMode == 0) {      
                currentValue = temp;
            }
            else if(displayMode == 1) {
                currentValue = moisture;
            }
            else {   
                currentValue = light;
            }
            if(displayMode != lastDisplayMode || currentValue != lastValue)
            {
                dspTask_OnLCD(displayMode, currentValue);
                lastDisplayMode = displayMode;
                lastValue = currentValue;
            }
        }
    }
}

void initSysPins(void)
{
    ANSELA = 0b00000000;
    ANSELB = 0b00100000;
    //ANSELC = 0b00000000;
    ANSELD = 0b00000100;
    ANSELE = 0b00000100;

    TRISA = 0b11000000;
    TRISB = 0b00100101;
    //TRISC = 0b10000000;
    TRISD = 0b00000100;
    TRISE = 0b00000100;

    RXPPS  = 0x17;
    RC6PPS = 0x10;
}
