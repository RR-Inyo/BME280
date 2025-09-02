/*
 * BME280.c - Library for controlling BME280-based temperature, humidity, and pressure sensor, source file
 * (c) 2025 @RR_Inyo
 * Released under the MIT license
 * https://opensource.org/licenses/mit-license.php
 */

#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/i2c_host/mssp1.h"
#include "mcc_generated_files/timer/delay.h"
#include "BME280.h"

// Functions to write to a register in BME280
void BME280_WriteRegister(uint8_t reg, uint8_t data)
{
    uint8_t buf[2];
    buf[0] = reg;
    buf[1] = data;
    while(I2C1_IsBusy()) {
        // Wait until I2C bus is available
    }
    I2C1_Write(BME280_ADDRESS, buf, 2);
    DELAY_microseconds(600);
}

// Function to read a register in BME280
uint8_t BME280_ReadRegister(uint8_t reg)
{
    uint8_t data;
    while(I2C1_IsBusy()) {
        // Wait until I2C bus is available
    }
    I2C1_WriteRead(BME280_ADDRESS, &reg, 1, &data, 1);
    //DELAY_microseconds(200);
    //I2C1_Write(BME280_ADDRESS, &reg, 1);
    //while(I2C1_IsBusy()) {
    //    // Wait until I2C bus is available
    //}
    //I2C1_Read(BME280_ADDRESS, &data, 1);
    DELAY_microseconds(600);
    
    return data;
}

// Functions to read from multiple registers in BME280
void BME280_ReadMultiRegisters(uint8_t reg, uint8_t *data, uint8_t len)
{  
    // Limit the maximum length to BME280_N_BUF
    if(len > BME280_N_BUF) {
        len = BME280_N_BUF;
    }
    
    while(I2C1_IsBusy()) {
        // Wait until I2C bus is available
    }
    I2C1_WriteRead(BME280_ADDRESS, &reg, 1, data, len);
    DELAY_microseconds(600);
}

void BME280_Reset(void)
{
    BME280_WriteRegister(BME280_RESET, 0xb6);
}

bool BME280_ReadID(void)
{
    uint8_t id = BME280_ReadRegister(BME280_ID);
    if (id != 0x60) {
        return true;
    }
    return false;
}

bool BME280_Initialize(void)
{
    BME280_Reset();
    DELAY_milliseconds(10);
    if (BME280_ReadID()) {
        return true;
    }
    
    DELAY_milliseconds(10);
    
    BME280_ReadTrimmingParameters();
    BME280_SetTemperatureOverSampling(BME280_OVERSAMPLE_1);
    BME280_SetPressureOverSampling(BME280_OVERSAMPLE_1);
    BME280_SetHumidityOverSampling(BME280_OVERSAMPLE_1);
    
    BME280_SetStandbyTime(BME280_STANDBY_125MS);
    BME280_SetMode(BME280_SLEEP_MODE);
    
    return false;
}

void BME280_ReadTrimmingParameters(void) {
    uint8_t buf[2];
    
    // Read trimming parameters for temperature
    // dig_T1
    BME280_ReadMultiRegisters(BME280_CALIB_00, buf, 2);
    BME280_dig_T1 = buf[1] << 8 | buf[0];
    
    // dig_T2
    BME280_ReadMultiRegisters(BME280_CALIB_02, buf, 2);
    BME280_dig_T2 = buf[1] << 8 | buf[0];
    
    // dig_T3
    BME280_ReadMultiRegisters(BME280_CALIB_04, buf, 2);
    BME280_dig_T3 = buf[1] << 8 | buf[0];
    
    // Read trimming parameters for pressure
    // dig_P1
    BME280_ReadMultiRegisters(BME280_CALIB_06, buf, 2);
    BME280_dig_P1 = buf[1] << 8 | buf[0];
    
    // dig_P2
    BME280_ReadMultiRegisters(BME280_CALIB_08, buf, 2);
    BME280_dig_P2 = buf[1] << 8 | buf[0];
    
    // dig_P3
    BME280_ReadMultiRegisters(BME280_CALIB_10, buf, 2);
    BME280_dig_P3 = buf[1] << 8 | buf[0];
    
    // dig_P4
    BME280_ReadMultiRegisters(BME280_CALIB_12, buf, 2);
    BME280_dig_P4 = buf[1] << 8 | buf[0];
    
    // dig_P5
    BME280_ReadMultiRegisters(BME280_CALIB_14, buf, 2);
    BME280_dig_P5 = buf[1] << 8 | buf[0];
    
    // dig_P6
    BME280_ReadMultiRegisters(BME280_CALIB_16, buf, 2);
    BME280_dig_P6 = buf[1] << 8 | buf[0];
    
    // dig_P7
    BME280_ReadMultiRegisters(BME280_CALIB_18, buf, 2);
    BME280_dig_P7 = buf[1] << 8 | buf[0];
    
    // dig_P8
    BME280_ReadMultiRegisters(BME280_CALIB_20, buf, 2);
    BME280_dig_P8 = buf[1] << 8 | buf[0];
    
    // dig_P9
    BME280_ReadMultiRegisters(BME280_CALIB_22, buf, 2);
    BME280_dig_P9 = buf[1] << 8 | buf[0];
    
    // Read trimming parameters for humidity
    // dig_H1
    BME280_dig_H1 = BME280_ReadRegister(BME280_CALIB_25);
    
    // dig_H2
    BME280_ReadMultiRegisters(BME280_CALIB_26, buf, 2);
    BME280_dig_H2 = buf[1] << 8 | buf[0];
    
    // dig_H3
    BME280_dig_H3 = BME280_ReadRegister(BME280_CALIB_28);
    
    // dig_H4
    BME280_ReadMultiRegisters(BME280_CALIB_29, buf, 2);
    BME280_dig_H4 = buf[0] << 4 | (buf[1] & 0b00001111);
    
    // dig_H5
    BME280_ReadMultiRegisters(BME280_CALIB_30, buf, 2);
    BME280_dig_H5 = buf[1] << 4 | (buf[0] >> 4);
    
    // Read trimming parameters for humidity
    // dig_H6
    BME280_dig_H6 = BME280_ReadRegister(BME280_CALIB_32);
}

void BME280_SetMode(uint8_t mode)
{
    mode &= 0b00000011;
    uint8_t buf;
    buf = BME280_ReadRegister(BME280_CTRL_MEAS);
    buf |= mode;
    BME280_WriteRegister(BME280_CTRL_MEAS, buf);
}

void BME280_SetStandbyTime(uint8_t time)
{
    time &= 0b00000111;
    uint8_t buf;
    buf = BME280_ReadRegister(BME280_CONFIG);
    buf |= (time << 5);
    BME280_WriteRegister(BME280_CONFIG, buf);
}

void BME280_SetFilter(uint8_t fil)
{
    fil &= 0b00000111;
    uint8_t buf;
    buf = BME280_ReadRegister(BME280_CONFIG);
    buf |= (fil << 2);
    BME280_WriteRegister(BME280_CONFIG, buf);
}

void BME280_SetTemperatureOverSampling(uint8_t os)
{
    os &= 0b00000111;
    uint8_t buf;
    buf = BME280_ReadRegister(BME280_CTRL_MEAS);
    buf |= (os << 5);
    BME280_WriteRegister(BME280_CTRL_MEAS, buf);
}

void BME280_SetPressureOverSampling(uint8_t os)
{
    os &= 0b00000111;
    uint8_t buf;
    buf = BME280_ReadRegister(BME280_CTRL_MEAS);
    buf |= (os << 2);
    BME280_WriteRegister(BME280_CTRL_MEAS, buf);
}

void BME280_SetHumidityOverSampling(uint8_t os)
{
    os &= 0b00000111;
    uint8_t buf;
    buf = BME280_ReadRegister(BME280_CTRL_HUM);
    buf |= os;
    BME280_WriteRegister(BME280_CTRL_HUM, buf);
}

void BME280_PerformMeasurement()
{
    BME280_SetMode(BME280_FORCED_MODE);
}

bool BME280_IsMeasurementOngoing(void)
{
    uint8_t meas = (BME280_ReadRegister(BME280_STATUS) & 0b00001000) >> 3;
    if(meas) {
        return true;
    }
    else {
        return false;
    }
}

int32_t BME280_GetTemperatureRaw(void)
{
    uint8_t buf[3];
    BME280_ReadMultiRegisters(BME280_TEMP_MSB, buf, 3);
    BME280_t_raw = ((uint32_t) buf[0]) << 12 | ((uint32_t) buf[1]) << 4 | ((uint32_t) buf[2]) >> 4;
    return BME280_t_raw;
}

int32_t BME280_GetPressureRaw(void)
{
    uint8_t buf[3];
    BME280_ReadMultiRegisters(BME280_PRESS_MSB, buf, 3);
    BME280_p_raw = ((uint32_t) buf[0]) << 12 | ((uint32_t) buf[1]) << 4 | ((uint32_t) buf[2]) >> 4;
    return BME280_p_raw;
}

int32_t BME280_GetHumidityRaw(void)
{
    uint8_t buf[2];
    BME280_ReadMultiRegisters(BME280_HUM_MSB, buf, 2);
    BME280_h_raw = ((uint16_t) buf[0]) << 8 | buf[1];
    return BME280_h_raw;
}

// Based on BME280 datasheet, Section 8.2
float BME280_GetTemperatureCelcius(void)
{
    int32_t var1, var2, t;
    int32_t adc_T = BME280_GetTemperatureRaw();
    
    var1 = ((((adc_T >> 3) - ((int32_t) BME280_dig_T1 << 1))) * ((int32_t) BME280_dig_T2)) >> 11;
    var2 = (((((adc_T >> 4) - ((int32_t) BME280_dig_T1)) * ((adc_T >> 4) - ((int32_t) BME280_dig_T1))) >> 12) * ((int32_t) BME280_dig_T3)) >> 14;
    BME280_t_fine = var1 + var2;
    t = (BME280_t_fine * 5 + 128) >> 8;
    return (float) t / 100.0;
}

// Based on BME280 datasheet, Section 8.2
float BME280_GetPressurehPa(void)
{
    int32_t var1, var2;
    uint32_t p;
    int32_t adc_P = BME280_GetPressureRaw();
    
    var1 = (((int32_t) BME280_t_fine) >> 1) - (int32_t) 64000;
    var2 = (((var1 >> 2) * (var1 >> 2)) >> 11) * ((int32_t) BME280_dig_P6);
    var2 = var2 + ((var1 * ((int32_t) BME280_dig_P5)) << 1);
    var2 = (var2 >> 2) + (((int32_t) BME280_dig_P4) << 16);
    var1 = (((BME280_dig_P3 * (((var1 >> 2) * (var1 >> 2)) >> 13)) >> 3) + ((((int32_t) BME280_dig_P2) * var1) >> 1)) >> 18;
    var1 = ((((32768 + var1)) * ((int32_t) BME280_dig_P1)) >> 15);
    if(var1 == 1) {
        return 0;
    }
    p = (((uint32_t)(((int32_t) 1048576) - adc_P) - (var2 >> 12))) * 3125;
    if (p < 0x80000000) {
        p = (p << 1) / ((uint32_t) var1); 
    }
    else {
        p = (p / (uint32_t) var1) * 2;
    }
    var1 = (((int32_t) BME280_dig_P9) * ((int32_t) (((p >> 3) * (p >> 3)) >> 13))) >> 12;
    var2 = (((int32_t) (p >> 2)) * ((int32_t) BME280_dig_P8)) >> 13;
    p = (uint32_t) ((int32_t) p + ((var1 + var2 + BME280_dig_P7) >> 4));
    
    return (float) p / 100.0;
}

// Based on BME280 datasheet, Section 8.2
float BME280_GetHumidityPercentRH(void)
{
    int32_t v_x1_u32r;
    uint32_t h;
    uint32_t adc_H = BME280_GetHumidityRaw();
    
    v_x1_u32r = (BME280_t_fine - ((int32_t) 76800));
    v_x1_u32r = (((((adc_H << 14) - (((int32_t) BME280_dig_H4) << 20) - (((int32_t) BME280_dig_H5) * v_x1_u32r)) 
            + ((int32_t) 16384)) >> 15) * (((((((v_x1_u32r * ((int32_t) BME280_dig_H6)) >> 10) * (((v_x1_u32r 
            * ((int32_t) BME280_dig_H3)) >> 11) + ((int32_t) 32768))) >> 10) + ((int32_t) 2097152)) 
            * ((int32_t) BME280_dig_H2) + 8192) >> 14));
    v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((int32_t) BME280_dig_H1)) >> 4));
    v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
    v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);
    h = (uint32_t) v_x1_u32r >> 12;
    return (float) h / 1024.0;
}
