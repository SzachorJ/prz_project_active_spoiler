#include "adxl345Handler.h"

ADXL_DATA tempAccelValues = {0, 0, 0};

void tcaAccelSelect(uint8_t channel)
{
    if (channel > 7)
        return;
    Wire.beginTransmission(TCAADDR);
    Wire.write(1 << channel);
    Wire.endTransmission();
}

void initializeAccelTransmission(uint8_t channel)
{
    if (channel > 7)
        return;
    tcaAccelSelect(channel);
    Wire.beginTransmission(ADXL345);
    Wire.write(0x2D);
    Wire.write(8);
    Wire.endTransmission();
    delay(10);
    Wire.beginTransmission(ADXL345);
    Wire.write(0x31);
    Wire.write(1);
    Wire.endTransmission();
    delay(10);
}

ADXL_DATA readAdxlData(uint8_t channel)
{
    tcaAccelSelect(channel);
    Wire.beginTransmission(ADXL345);
    Wire.write(0x32);
    Wire.endTransmission(false);
    Wire.requestFrom(ADXL345, 6, true);
    tempAccelValues.x_position = (Wire.read() | Wire.read() << 8);
    tempAccelValues.x_position = tempAccelValues.x_position / 128;
    tempAccelValues.y_position = (Wire.read() | Wire.read() << 8);
    tempAccelValues.y_position = tempAccelValues.y_position / 128;
    tempAccelValues.z_position = (Wire.read() | Wire.read() << 8);
    tempAccelValues.z_position = tempAccelValues.z_position / 128;

    return tempAccelValues;
}
