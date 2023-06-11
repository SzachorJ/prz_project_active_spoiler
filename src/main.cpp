#include <Arduino.h>
#include <SoftwareSerial.h>
#include "adxl345Handler.h"
#include "servoHandler.h"
#include "fuzzyLogic.h"
#include "logger.h"
#include "sdHandler.h"
#include "helpers.h"

#define rxPin 2
#define txPin 3

Servo lServo, rServo;

int lpos, rpos;

String outputString;

SoftwareSerial Serial2 = SoftwareSerial(rxPin, txPin);

ADXL_DATA adxl0 = {0, 0, 0};
ADXL_DATA adxl1 = {0, 0, 0};
ADXL_DATA adxl2 = {0, 0, 0};
ADXL_DATA adxl3 = {0, 0, 0};
ADXL_DATA average = {0, 0, 0};

CONVERTED_DATA convertedData = {0, 0, 0};

FUZZY_OUTPUT fuzzyOutput = {0, 0};

int channels = 3;
int isNegativeLeft = 0;
int isNegativeRight = 0;

int final_left_position;
int final_right_position;

void setup()
{
    pinMode(rxPin, INPUT);
    pinMode(txPin, OUTPUT);

    Serial.begin(115200);
    Serial2.begin(115200);
    Wire.begin();
    for (int i = 0; i < channels; i++)
    {
        initializeTransmission(i);
    }
    setUpFuzzyLogic();
    initializeServo(9, 8, lServo, rServo);
}

void loop()
{
    adxl0 = readAdxlData(0);
    adxl1 = readAdxlData(1);
    adxl2 = readAdxlData(2);
    adxl3 = readAdxlData(3);

    average.x_position = getAverage(adxl0.x_position, adxl1.x_position, adxl2.x_position, adxl3.x_position);
    average.y_position = getAverage(adxl0.y_position, adxl1.y_position, adxl2.y_position, adxl3.y_position);

    if (average.x_position > 0 && average.x_position > 1)
        average.x_position = 1;
    if (average.x_position < 0 && average.x_position < -1)
        average.x_position = -1;

    if (average.y_position > 0 && average.y_position > 1)
        average.y_position = 1;
    if (average.y_position < 0 && average.y_position < -1)
        average.y_position = -1;

    fuzzyOutput = getFuzzyOutput(average.x_position, average.y_position);

    if (fuzzyOutput.left_position < 0)
        isNegativeLeft = 1;
    else
        isNegativeLeft = 0;

    if (fuzzyOutput.right_position < 0)
        isNegativeRight = 1;
    else
        isNegativeRight = 0;

    final_left_position = abs(fuzzyOutput.left_position);
    final_right_position = abs(fuzzyOutput.right_position);

    setServoPosition(final_left_position, isNegativeLeft, lServo);
    setServoPosition(final_right_position, isNegativeRight, rServo);

    lpos = 180 - returnServoPosition(final_left_position, isNegativeLeft);
    rpos = returnServoPosition(final_right_position, isNegativeRight);

    Serial.println(lpos);
    Serial.println(rpos);

    outputString = stringAssembler(average.x_position, average.y_position, lpos, rpos);

    Serial2.println(outputString);

    delay(100);
}