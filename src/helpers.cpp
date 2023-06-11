#include "helpers.h"

float getAverage(float a, float b, float c, float d)
{
    float result = (a - b + c + d) / 3;
    return result;
}

String stringAssembler(float xf, float yf, int l, int p)
{
    String outputString = "<";
    outputString += ";";
    outputString += String(xf);
    outputString += ";";
    outputString += String(yf);
    outputString += ";";
    outputString += String(l);
    outputString += ";";
    outputString += String(p);
    outputString += ";>";

    return outputString;
}
