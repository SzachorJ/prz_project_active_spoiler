#include "servoHandler.h"

void initializeServo(int pin1, int pin2, Servo servo1, Servo servo2)
{
    servo1.attach(pin1);
    servo2.attach(pin2);
    servo1.write(NEUTRAL_POSITION);
    servo2.write(NEUTRAL_POSITION);
}

int returnServoPosition(int position, int isNegative)
{

    if (position > 90)
        position = 90;

    if (position < 0)
        position = 0;

    if (isNegative == 1)
    {
        return NEUTRAL_POSITION - position;
    }
    if (isNegative == 0)
    {
        return NEUTRAL_POSITION + position;
    }
}

void setServoPosition(int position, int isNegative, Servo servo)
{

    if (position > 90)
        position = 90;

    if (position < 0)
        position = 0;

    if (isNegative == 1)
        servo.write(NEUTRAL_POSITION - position);
    if (isNegative == 0)
        servo.write(NEUTRAL_POSITION + position);
}