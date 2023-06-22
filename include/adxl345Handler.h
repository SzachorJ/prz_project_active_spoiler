#ifndef ADXL345HANDLER_H
#define ADXL345HANDLER_H

#include <Arduino.h>
#include <Wire.h>

#define TCAADDR 0x70
#define ADXL345 0x53

typedef struct _adxl_data_
{
    float x_position;
    float y_position;
    float z_position;

} ADXL_DATA;

typedef struct _converted_data_
{
    uint32_t x_position;
    uint32_t y_position;
    uint32_t z_position;

} CONVERTED_DATA;

void tcaAccelSelect(uint8_t channel);

void initializeAccelTransmission(uint8_t channel);

ADXL_DATA readAdxlData(uint8_t channel);

#endif