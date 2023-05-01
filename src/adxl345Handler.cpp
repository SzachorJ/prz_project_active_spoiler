#include "adxl345Handler.h"

ADXL_DATA tempValues = {0, 0, 0};

void tcaSelect(uint8_t channel)
{
    if (channel > 7)
        return;
    Wire.beginTransmission(TCAADDR);
    Wire.write(1 << channel);
    Wire.endTransmission();
}

void initializeTransmission(uint8_t channel)
{
    if (channel > 7)
        return;
    tcaSelect(channel);
    Wire.beginTransmission(ADXL345);
    Wire.write(0x2D);
    Wire.write(8);
    Wire.endTransmission();
    delay(10);
}

ADXL_DATA readAdxlData(uint8_t channel)
{
    tcaSelect(channel);
    Wire.beginTransmission(ADXL345);
    Wire.write(0x32);
    Wire.endTransmission(false);
    Wire.requestFrom(ADXL345, 6, true);
    tempValues.x_position = (Wire.read() | Wire.read() << 8);
    tempValues.x_position = tempValues.x_position / 256;
    tempValues.y_position = (Wire.read() | Wire.read() << 8);
    tempValues.y_position = tempValues.y_position / 256;
    tempValues.z_position = (Wire.read() | Wire.read() << 8);
    tempValues.z_position = tempValues.z_position / 256;

    return tempValues;
}

CONVERTED_DATA convertData(ADXL_DATA data)
{
}
