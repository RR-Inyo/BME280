# A library for MPLAB XC8 to obtain data from BME280 sensors

## Introduction
I created a C-language library for Microchip's MPLAB XC8 C-language compiler for the PIC microcontrollers to communicate with and obtain data from the Bosch BME280 air temperature, humidity, and pressure sensor. The communication between the PIC microcontroller and the BME280 sensor relies on the I2C.

Unlike other I2C/SPI communication-based sensors, the BME280 needs complicated calculations to obtain the correct temperature, humidity, and pressure. Fortunately, sample C-language codes are presented in the BME280 datasheet, of which my code here is an implementation to MPLAB XC8.

You can use my library by properly copying the header (`.h`) and the source (`.c`) files to your project and by placing `#include "BME280.h"` in your code.

I have tested this library on PIC16F19155 only.

## Functions and how to use them
### I2C communications
#### `void BME280_WriteRegister(uint8_t reg, uint8_t data)`
Call this function to write a byte to a register inside the BME280. Usually, the user do not need to use this function explicitly because other more abstruct functions call this one to communicate with the BME280 via I2C.
`reg` is the register address (a.k.a. subaddress) and `data` is the data to be sent. 

#### `uint8_t BME280_ReadRegister(uint8_t reg)`
Call this function to read a byte from a register inside the BME280. It returns a byte. Usually, the user do not need to use this function explicitly because other more abstruct functions call this one to communicate with the BME280 via I2C.
`reg` is the register address (a.k.a. subaddress).

#### `void BME280_ReadMultiRegisters(uint8_t reg, uint8_t *data, uint8_t len)`
Call this function to read multiple bytes from the BME280. The received bytes are stored in `data` as the function takes its pointer. `len` is the length of the bytes. The maximum number of `len` is 4. If `len` exceeds 4, it will be limited to 4 inside this function. Usually, the user do not need to use this function explicitly because other more abstruct functions call this one to communicate with the BME280 via I2C.

#### `void BME280_Reset(void)`
Call this function to perform the power-on reset.

#### `bool BME280_ReadID(void)`
Call this function to read the ID of the BME280. As written in the BME280 datasheet, the ID must be `0x60` read out from ID register at '0xd0'. If the received data contradicts `0x60`, this function returns `true`.

#### `bool BME280_Initialize(void)`
Call this function to initialize the BME280. In my library, oversampling rates are selected 1 for all of temperature, humidity, and pressure. The standby time is chosen to be 125 ms. The BME280 gets into SLEEP mode in this function.

#### `void BME280_ReadTrimmingParameters(void)`
Call this functuion to read trimming parameters from the BME280. As written in the BME280 datasheet, each one of the BME280 device has its own trimming parameters which were calibrated in the factory. To use a BME280, you need to read the trimming parameters stored in the registers and properly use those parameters to calculate the temperaure, humidity, and pressure. The received trimming parameters will be stored in global variables defined in the header (`.h`) file.

Usually, the user do not need to use this function explicitly because the `BME280_Initialize()` function calls this function to initialize the BME280.

#### `void BME280_SetMode(uint8_t mode)`
Call this functuion to set the measurement mode of the BME280. Inside the header (`.h`) file, `BME280_SLEEP_MODE`, `BME280_FORCED_MODE`, and `BME280_NORMAL_MODE` are defined. See the BME280 datasheet for the meaning of these modes.

#### `void BME280_SetStandbyTime(uint8_t time)`
Call this function to set the measurement standby time. The standby time is only applicable in the Normal Mode. Inside the header (`.h`) file, 

#### `void BME280_SetFilter(uint8_t fil)`
Call this function to set the IIR filter configurations in the BME280. Inside the header (`.h`) file, constants from `BME280_STANDBY_500US` to `BME280_FILTER_16` are defined. As far as I understand, this IIR filter is applicable for all of the temperature, humidity, and pressure measurements.

#### `void BME280_SetTemperatureOverSampling(uint8_t os)`
Call this function to set the oversampling configurations for the temperature measurement. Inside the header (`.h`) file, constants from ` BME280_OVERSAMPLE_NONE` to `BME280_OVERSAMPLE_16` are defined.

#### `void BME280_SetPressueOverSampling(uint8_t os)`
Call this function to set the oversampling configurations for the pressure measurement. Inside the header (`.h`) file, constants from ` BME280_OVERSAMPLE_NONE` to `BME280_OVERSAMPLE_16` are defined.

#### `void BME280_SetHumidityOverSampling(uint8_t os)`
Call this function to set the oversampling configurations for the humidity measurement. Inside the header (`.h`) file, constants from ` BME280_OVERSAMPLE_NONE` to `BME280_OVERSAMPLE_16` are defined.



