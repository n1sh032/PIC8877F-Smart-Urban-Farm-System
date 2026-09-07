Smart Urban Farm System

PIC16F18877 project that monitors soil moisture, temperature and light, and automatically controls a water pump and fan. Sensor readings and warnings are shown on an LCD and also sent out over UART.

What it does
Reads three sensors on a round-robin, using interrupt-driven ADC (non-blocking)
Turns the fan on/off based on temperature
Turns the pump on/off and adjusts speed (via PWM) based on soil moisture
Turns on an LED when light level is low
Push button cycles what's shown on the LCD (temp / moisture / light)
Toggle switch puts the system into a low power standby mode
Sends live readings and warnings to a PC over UART
Pins
Signal	Pin
Temperature sensor	RE2
Soil moisture sensor	RB5
LDR (light sensor)	RD2
Push button (cycle LCD)	RB0, ext. interrupt
Toggle switch (LPM)	RB2
LCD data	RD4–RD7
LCD RS / E	RE0 / RE1
Pump / fan output	RD0 / RD1
PWM (motor speed)	RD3
Light LED	RA1
LPM LED	RA0
UART TX	RC6
UART RX	RC7 (not used yet)
Files
config.h — oscillator/config settings
main.c — main loop, ties everything together
adc.c — ADC setup + conversion (interrupt-driven)
pwm.c — PWM setup and duty cycle presets
motor.c — pump/fan on/off
extint.c — external interrupt setup
isr.c — interrupt handler
lcd.c — LCD driver (4-bit mode)
dspTask.c — writes sensor values to the LCD
uart.c — UART setup and transmit functions
lpm.c — low power mode switch + logic
How the main loop works
Check if the LPM switch is on. If yes, stop the pump/fan, blank the display to "Low Power Mode", and skip everything else.
If not in LPM: check if the current ADC conversion finished. If it has, convert the reading, send it over UART, and start the next sensor's conversion.
Run the fan/pump/LED logic based on the latest readings.
Update the LCD only if the mode or value actually changed.

Nothing in the loop blocks — the ADC runs in the background and interrupts when done, so the rest of the loop keeps running the whole time.

Build

MPLAB X + XC8, target PIC16F18877, programmed via PICkit-4.

Viewing UART output

Connect the CH340 module on RC6/RC7, 9600 baud, 8N1. Any serial terminal works (PuTTY, MPLAB Data Visualizer, or the included serial_terminal.html, a simple browser-based terminal — needs Chrome or Edge).
