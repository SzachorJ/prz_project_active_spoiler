#include <Arduino.h>
#include "adxl345Handler.h"
#include "servoHandler.h"
#include "fuzzyLogic.h"
#include "logger.h"
#include "sdHandler.h"
#include "helpers.h"

Servo lServo, rServo;

ADXL_DATA adxl0 = {0, 0, 0};
ADXL_DATA adxl1 = {0, 0, 0};
ADXL_DATA adxl2 = {0, 0, 0};
ADXL_DATA adxl3 = {0, 0, 0};
ADXL_DATA adxl4 = {0, 0, 0};
ADXL_DATA average = {0, 0, 0};

CONVERTED_DATA convertedData = {0, 0, 0};

FUZZY_OUTPUT fuzzyOutput = {0, 0};

int channels = 5;
int isNegativeLeft = 0;
int isNegativeRight = 0;

int final_left_position;
int final_right_position;

void setup()
{
    Serial.begin(9600);
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
    adxl4 = readAdxlData(4);

    average.x_position = getAverage(adxl0.x_position, adxl1.x_position, adxl2.x_position, adxl3.x_position, adxl4.x_position);
    average.y_position = getAverage(adxl0.y_position, adxl1.y_position, adxl2.y_position, adxl3.y_position, adxl4.y_position);

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

    // Serial.print("x axis: ");
    // Serial.print(dominant.x_position);
    // Serial.print(" y axis: ");
    // Serial.println(dominant.y_position);

    // Serial.print("left position: ");
    // Serial.print(fuzzyOutput.left_position);
    // Serial.print(" right position: ");
    // Serial.println(fuzzyOutput.right_position);

    // Serial.print("final left position: ");
    // Serial.print(final_left_position);
    // Serial.print(" final right position: ");
    // Serial.println(final_right_position);
    // Serial.println();

    delay(10);
}