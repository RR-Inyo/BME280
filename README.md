# A library for MPLAB XC8 to obtain data from BME280 sensors

## Introduction
I created a C-language library for Microchip's MPLAB XC8 C-language compiler for the PIC microcontrollers to communicate with and obtain data from the Bosch BME280 air temperature, humidity, and pressure sensor. The communication between the PIC microcontroller and the BME280 sensor relies on the I2C.

Unlike other I2C/SPI communication-based sensors, the BME280 needs complicated calculations to obtain the correct temperature, humidity, and pressure. Fortunately, sample C-language codes are presented in the BME280 datasheet, of which my code here is an implementation to MPLAB XC8.

You can use my library by properly copying the .h and .c files to your project and by placing `#include "BME280.h"` in your code.

I have tested this library on PIC16F19155 only.

## Functions and how to use them
### I2C communications
#### `void BME280_WriteRegister(uint8_t reg, uint8_t data)`
Call this function to write a data to a register inside the BME280. Usually, the user do not need to use this function explicitly because other more abstruct functions call this one to communicate with the BME280 via I2C.
`reg` is the register address (a.k.a. subaddress) and `data` is the data to be sent. 

#### 
