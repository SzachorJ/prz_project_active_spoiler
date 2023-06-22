#include "L3G4200DHandler.h"

L3G4200D_DATA tempGyroValues = {0, 0, 0};

void tcaGyroSelect(uint8_t channel)
{
    if (channel > 7)
        return;
    Wire.beginTransmission(TCAADDR);
    Wire.write(1 << channel);
    Wire.endTransmission();
}

void initializeGyroTransmission(uint8_t channel, int scale)
{
    if (channel > 7)
        return;
    tcaGyroSelect(channel);
    writeRegister(L3G4200D, CTRL_REG1, 0b00001111);

    writeRegister(L3G4200D, CTRL_REG2, 0b00000000);

    writeRegister(L3G4200D, CTRL_REG3, 0b00001000);

    if (scale == 250)
    {
        writeRegister(L3G4200D, CTRL_REG4, 0b00000000);
    }
    else if (scale == 500)
    {
        writeRegister(L3G4200D, CTRL_REG4, 0b00010000);
    }
    else
    {
        writeRegister(L3G4200D, CTRL_REG4, 0b00110000);
    }

    writeRegister(L3G4200D, CTRL_REG5, 0b00000000);
}

L3G4200D_DATA readL3G4200DData(uint8_t channel)
{
    tcaGyroSelect(channel);

    byte xMSB = readRegister(L3G4200D, 0x29);
    byte xLSB = readRegister(L3G4200D, 0x28);
    tempGyroValues.x_roll = ((xMSB << 8) | xLSB);

    byte yMSB = readRegister(L3G4200D, 0x2B);
    byte yLSB = readRegister(L3G4200D, 0x2A);
    tempGyroValues.y_roll = ((yMSB << 8) | yLSB);

    byte zMSB = readRegister(L3G4200D, 0x2D);
    byte zLSB = readRegister(L3G4200D, 0x2C);
    tempGyroValues.z_roll = ((zMSB << 8) | zLSB);

    return tempGyroValues;
}
