/*
 * BME280.h - Library for controlling BME280-based temperature, humidity, and pressure sensor, header file
 * (c) 2025 @RR_Inyo
 * Released under the MIT license
 * https://opensource.org/licenses/mit-license.php
 */

#ifndef BME280_H
#define	BME280_H

#ifdef	__cplusplus
extern "C" {
#endif

// Constants (I2C address, register addresses, etc.)
#define BME280_ADDRESS          0x76
#define BME280_HUM_LSB          0xfe
#define BME280_HUM_MSB          0xfd
#define BME280_TEMP_XLSB        0xfc
#define BME280_TEMP_LSB         0xfb
#define BME280_TEMP_MSB         0xfa
#define BME280_PRESS_XLSB       0xf9
#define BME280_PRESS_LSB        0xf8
#define BME280_PRESS_MSB        0xf7
#define BME280_CONFIG           0xf5
#define BME280_CTRL_MEAS        0xf4
#define BME280_STATUS           0xf3
#define BME280_CTRL_HUM         0xf2
#define BME280_CALIB_41         0xf0
#define BME280_CALIB_40         0xef
#define BME280_CALIB_39         0xee
#define BME280_CALIB_38         0xed
#define BME280_CALIB_37         0xec
#define BME280_CALIB_36         0xeb
#define BME280_CALIB_35         0xea
#define BME280_CALIB_34         0xe9
#define BME280_CALIB_33         0xe8
#define BME280_CALIB_32         0xe7
#define BME280_CALIB_31         0xe6
#define BME280_CALIB_30         0xe5
#define BME280_CALIB_29         0xe4
#define BME280_CALIB_28         0xe3
#define BME280_CALIB_27         0xe2
#define BME280_CALIB_26         0xe1
#define BME280_RESET            0xe0
#define BME280_ID               0xd0
#define BME280_CALIB_25         0xa1
#define BME280_CALIB_24         0xa0
#define BME280_CALIB_23         0x9f
#define BME280_CALIB_22         0x9e
#define BME280_CALIB_21         0x9d
#define BME280_CALIB_20         0x9c
#define BME280_CALIB_19         0x9b
#define BME280_CALIB_18         0x9a
#define BME280_CALIB_17         0x99
#define BME280_CALIB_16         0x98
#define BME280_CALIB_15         0x97
#define BME280_CALIB_14         0x96
#define BME280_CALIB_13         0x95
#define BME280_CALIB_12         0x94
#define BME280_CALIB_11         0x93
#define BME280_CALIB_10         0x92
#define BME280_CALIB_09         0x91
#define BME280_CALIB_08         0x90
#define BME280_CALIB_07         0x8f
#define BME280_CALIB_06         0x8e
#define BME280_CALIB_05         0x8d
#define BME280_CALIB_04         0x8c
#define BME280_CALIB_03         0x8b
#define BME280_CALIB_02         0x8a
#define BME280_CALIB_01         0x89
#define BME280_CALIB_00         0x88
   
#define BME280_STANDBY_500US    0x00
#define BME280_STANDBY_62R5MS   0x01
#define BME280_STANDBY_125MS    0x02
#define BME280_STANDBY_250MS    0x03
#define BME280_STANDBY_500MS    0x04
#define BME280_STANDBY_1S       0x05
#define BME280_STANDBY_10MS     0x06
#define BME280_STANDBY_20MS     0x07
    
#define BME280_FILTER_OFF       0x00
#define BME280_FILTER_2         0x01
#define BME280_FILTER_4         0x02
#define BME280_FILTER_8         0x03
#define BME280_FILTER_16        0x04

#define BME280_OVERSAMPLE_NONE  0x00
#define BME280_OVERSAMPLE_1     0x01
#define BME280_OVERSAMPLE_2     0x02
#define BME280_OVERSAMPLE_4     0x03
#define BME280_OVERSAMPLE_8     0x04
#define BME280_OVERSAMPLE_16    0x05

#define BME280_SLEEP_MODE       0x00
#define BME280_FORCED_MODE      0x01
#define BME280_NORMAL_MODE      0x11

#define BME280_N_BUF            4

// Function prototypes
void BME280_WriteRegister(uint8_t reg, uint8_t data);
uint8_t BME280_ReadRegister(uint8_t reg);
void BME280_ReadMultiRegisters(uint8_t reg, uint8_t *data, uint8_t len);
void BME280_Reset(void);
bool BME280_ReadId(void);
bool BME280_Initialize(void);
void BME280_ReadTrimmingParameters(void);
void BME280_SetMode(uint8_t);
void BME280_SetStandbyTime(uint8_t);
void BME280_SetFilter(uint8_t);
void BME280_SetTemperatureOverSampling(uint8_t);
void BME280_SetPressureOverSampling(uint8_t);
void BME280_SetHumidityOverSampling(uint8_t);
void BME280_PerformMeasurement(void);
bool BME280_IsMeasurementOngoing(void);
int32_t BME280_GetTemperatureRaw(void);
int32_t BME280_GetPressureRaw(void);
int32_t BME280_GetHumidityRaw(void);
float BME280_GetTemperatureCelcius(void);
float BME280_GetPressurehPa(void);
float BME280_GetHumidityPercentRH(void);

// Trimming parameters as global variables, temperature
uint32_t BME280_t_raw, BME280_p_raw;
uint16_t BME280_h_raw;

int32_t BME280_t_fine;
uint16_t BME280_dig_T1;
int16_t BME280_dig_T2, BME280_dig_T3;

// Trimming parameters as global variables, pressure
uint16_t BME280_dig_P1;
int16_t BME280_dig_P2, BME280_dig_P3, BME280_dig_P4, BME280_dig_P5;
int16_t BME280_dig_P6, BME280_dig_P7, BME280_dig_P8, BME280_dig_P9;

// Trimming parameters as global variables, humidity
uint8_t BME280_dig_H1;
int16_t BME280_dig_H2;
uint8_t BME280_dig_H3;
int16_t BME280_dig_H4;
int16_t BME280_dig_H5;
int8_t BME280_dig_H6;

#ifdef	__cplusplus
}
#endif

#endif	/* BME280_H */

