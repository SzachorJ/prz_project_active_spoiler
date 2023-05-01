#ifndef SERVOHANDLER_H
#define SERVOHANDLER_H

#include <Arduino.h>
#include <Servo.h>

#define MIN_SERVO_POSITION 0
#define NEUTRAL_POSITION 90
#define MAX_SERVO_POSITION 180

void initializeServo(int pin1, int pin2, Servo servo1, Servo servo2);
void setServoPosition(int position, int isNegative, Servo servo);

#endif