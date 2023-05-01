#ifndef FUZZYLOGIC_H
#define FUZZYLOGIC_H

#include <Arduino.h>
#include <Fuzzy.h>

typedef struct _fuzzy_output_
{
    float left_position;
    float right_position;

} FUZZY_OUTPUT;

void setUpFuzzyLogic();

FUZZY_OUTPUT getFuzzyOutput(float input_x, float input_y);

#endif