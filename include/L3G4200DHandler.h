#ifndef L3G4200DHANDLER_H
#define L3G4200DHANDLER_H

#include <Arduino.h>
#include <Wire.h>
#include "i2cHandler.h"

#define TCAADDR 0x70
#define L3G4200D 0x69

#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24

typedef struct _l3g4200d_data_
{
    float x_roll;
    float y_roll;
    float z_roll;

} L3G4200D_DATA;

void tcaGyroSelect(uint8_t channel);

void initializeGyroTransmission(uint8_t channel, int scale);

L3G4200D_DATA readL3G4200DData(uint8_t channel);

#endif