#ifndef I2CHANDLER_H
#define I2CHANDLER_H

#include <Arduino.h>
#include <Wire.h>

void writeRegister(int deviceAddress, byte address, byte val);

int readRegister(int deviceAddress, byte address);

#endif