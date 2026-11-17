# Smart Urban Farm System

PIC16F18877 project that monitors soil moisture, temperature and light, and automatically controls a water pump and fan. Sensor readings and warnings are shown on an LCD and also sent out over UART.

## What it does

- Reads three sensors on a round-robin, using interrupt-driven ADC (non-blocking)
- Turns the fan on/off based on temperature
- Turns the pump on/off and adjusts speed (via PWM) based on soil moisture
- Turns on an LED when light level is low
- Push button cycles what's shown on the LCD (temp / moisture / light)
- Toggle switch puts the system into a low power standby mode
- Sends live readings and warnings to a PC over UART

## Pins

| Signal | Pin |
|---|---|
| Temperature sensor | RE2 (ADPCH 0x22) |
| Soil moisture sensor | RB5 (ADPCH 0x0D) |
| LDR (light sensor) | RD2 (ADPCH 0x1A) |
| Push button (cycle LCD) | RB0, ext. interrupt |
| Toggle switch (LPM) | RB2 |
| LCD data | RD4–RD7 |
| LCD RS / E | RE0 / RE1 |
| Pump / fan output | RD0 / RD1 |
| PWM (motor speed) | RD3 |
| Light LED | RA1 |
| LPM LED | RA0 |
| UART TX | RC6 |
| UART RX | RC7 (not used yet) |

## Files

. config.h — oscillator/config settings

. main.c — main loop, ties everything together

. adc.c — ADC setup + conversion (interrupt-driven)

. pwm.c — PWM setup and duty cycle presets

. motor.c — pump/fan on/off

. extint.c — external interrupt setup

. isr.c — interrupt handler

. lcd.c — LCD driver (4-bit mode)

. dspTask.c — writes sensor values to the LCD

. uart.c — UART setup and transmit functions

. lpm.c — low power mode switch + logic


## How the main loop works

1. When RB2 is high, enter software standby and display "Low Power Mode" once. The pump and fan stop and the ADC scan pauses after its pending conversion. When RB2 goes low, resume the scan and normal display.
2. If not in LPM: check if the current ADC conversion finished. If it has, convert the reading, send it over UART, and start the next sensor's conversion.
3. Run the fan/pump/LED logic based on the latest readings.
4. Update the LCD only if the mode or value actually changed.

ADC conversion completes via interrupt. LCD writes and UART transmissions are still synchronous. Temperature and dry-soil warnings are sent once per threshold crossing. The pump turns off at 70% or above and restarts at 65% or below. It runs at full PWM below 30% and at 25% PWM otherwise.

## Build

MPLAB X + XC8, target PIC16F18877. The source requires the board's local `config.h` with oscillator settings and configuration bits. This file and MPLAB project metadata are absent from the repository. Pin numbers depend on the package. See the [Microchip data sheet](https://www.microchip.com/content/dam/mchp/documents/MCU08/ProductDocuments/DataSheets/PIC16LF1885777_Data_Sheet_40001825F.pdf) for the package pinout and ADC channel table.

## Viewing UART output

Connect RC6 (UART TX) to the USB serial adapter's RX and share ground. Use a serial terminal such as PuTTY or MPLAB Data Visualizer at 9600 baud, 8N1.

## Not done yet / known limitations

- LPM is a software standby, not real hardware sleep — the CPU keeps running, it just stops updating the display and actuators
- UART only sends data out right now, doesn't receive commands
- IOC hasn't been added as its own feature yet
- The fan and light thresholds do not have hysteresis
- The firmware changes have not been checked on hardware
