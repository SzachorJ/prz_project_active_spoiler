#include "fuzzyLogic.h"

Fuzzy *fuzzy = new Fuzzy();

FUZZY_OUTPUT tempFuzzyOutput = {0, 0};

void setUpFuzzyLogic()
{
    FuzzyInput *x_axis = new FuzzyInput(1);
    FuzzySet *back = new FuzzySet(-100, -100, -100, -20);
    x_axis->addFuzzySet(back);
    FuzzySet *middle = new FuzzySet(-100, 0, 0, 100);
    x_axis->addFuzzySet(middle);
    FuzzySet *front = new FuzzySet(20, 100, 100, 100);
    x_axis->addFuzzySet(front);
    fuzzy->addFuzzyInput(x_axis);

    FuzzyInput *y_axis = new FuzzyInput(2);
    FuzzySet *left = new FuzzySet(-100, -100, -100, -20);
    y_axis->addFuzzySet(left);
    FuzzySet *center = new FuzzySet(-100, 0, 0, 100);
    y_axis->addFuzzySet(center);
    FuzzySet *right = new FuzzySet(20, 100, 100, 100);
    y_axis->addFuzzySet(right);
    fuzzy->addFuzzyInput(y_axis);

    FuzzyOutput *leftPosition = new FuzzyOutput(1);
    FuzzySet *left_tilt_right = new FuzzySet(-90, -90, -90, 0);
    leftPosition->addFuzzySet(left_tilt_right);
    FuzzySet *left_middle = new FuzzySet(-90, -10, 10, 90);
    leftPosition->addFuzzySet(left_middle);
    FuzzySet *left_tilt_left = new FuzzySet(0, 90, 90, 90);
    leftPosition->addFuzzySet(left_tilt_left);
    fuzzy->addFuzzyOutput(leftPosition);

    FuzzyOutput *rightPosition = new FuzzyOutput(2);
    FuzzySet *right_tilt_right = new FuzzySet(-90, -90, -90, 0);
    rightPosition->addFuzzySet(right_tilt_right);
    FuzzySet *right_middle = new FuzzySet(-90, -10, 10, 90);
    rightPosition->addFuzzySet(right_middle);
    FuzzySet *right_tilt_left = new FuzzySet(0, 90, 90, 90);
    rightPosition->addFuzzySet(right_tilt_left);
    fuzzy->addFuzzyOutput(rightPosition);

    FuzzyRuleAntecedent *ifXfrontAndYleft = new FuzzyRuleAntecedent();
    ifXfrontAndYleft->joinWithAND(front, left);
    FuzzyRuleAntecedent *ifXfrontAndYneutral = new FuzzyRuleAntecedent();
    ifXfrontAndYneutral->joinWithAND(front, center);
    FuzzyRuleAntecedent *ifXfrontAndYright = new FuzzyRuleAntecedent();
    ifXfrontAndYright->joinWithAND(front, right);

    FuzzyRuleAntecedent *ifXneutralAndYleft = new FuzzyRuleAntecedent();
    ifXneutralAndYleft->joinWithAND(middle, left);
    FuzzyRuleAntecedent *ifXneutralAndYneutral = new FuzzyRuleAntecedent();
    ifXneutralAndYneutral->joinWithAND(middle, center);
    FuzzyRuleAntecedent *ifXneutralAndYright = new FuzzyRuleAntecedent();
    ifXneutralAndYright->joinWithAND(middle, right);

    FuzzyRuleAntecedent *ifXbackAndYleft = new FuzzyRuleAntecedent();
    ifXbackAndYleft->joinWithAND(back, left);
    FuzzyRuleAntecedent *ifXbackAndYneutral = new FuzzyRuleAntecedent();
    ifXbackAndYneutral->joinWithAND(back, center);
    FuzzyRuleAntecedent *ifXbackAndYright = new FuzzyRuleAntecedent();
    ifXbackAndYright->joinWithAND(back, right);

    FuzzyRuleConsequent *thenTiltLeft = new FuzzyRuleConsequent();
    thenTiltLeft->addOutput(left_tilt_left);
    thenTiltLeft->addOutput(right_tilt_left);
    FuzzyRuleConsequent *thenStayNeutral = new FuzzyRuleConsequent();
    thenStayNeutral->addOutput(left_middle);
    thenStayNeutral->addOutput(right_middle);
    FuzzyRuleConsequent *thenTiltRight = new FuzzyRuleConsequent();
    thenTiltRight->addOutput(left_tilt_right);
    thenTiltRight->addOutput(right_tilt_right);
    FuzzyRuleConsequent *thenTiltFront = new FuzzyRuleConsequent();
    thenTiltFront->addOutput(left_tilt_right);
    thenTiltFront->addOutput(right_tilt_left);

    FuzzyRule *fuzzyRule01 = new FuzzyRule(1, ifXfrontAndYleft, thenTiltRight);
    fuzzy->addFuzzyRule(fuzzyRule01);
    FuzzyRule *fuzzyRule02 = new FuzzyRule(2, ifXfrontAndYneutral, thenTiltFront);
    fuzzy->addFuzzyRule(fuzzyRule02);
    FuzzyRule *fuzzyRule03 = new FuzzyRule(3, ifXfrontAndYright, thenTiltLeft);
    fuzzy->addFuzzyRule(fuzzyRule03);

    FuzzyRule *fuzzyRule04 = new FuzzyRule(4, ifXneutralAndYleft, thenTiltRight);
    fuzzy->addFuzzyRule(fuzzyRule04);
    FuzzyRule *fuzzyRule05 = new FuzzyRule(5, ifXneutralAndYneutral, thenStayNeutral);
    fuzzy->addFuzzyRule(fuzzyRule05);
    FuzzyRule *fuzzyRule06 = new FuzzyRule(6, ifXneutralAndYright, thenTiltLeft);
    fuzzy->addFuzzyRule(fuzzyRule06);

    FuzzyRule *fuzzyRule07 = new FuzzyRule(7, ifXbackAndYleft, thenTiltRight);
    fuzzy->addFuzzyRule(fuzzyRule07);
    FuzzyRule *fuzzyRule08 = new FuzzyRule(8, ifXbackAndYneutral, thenStayNeutral);
    fuzzy->addFuzzyRule(fuzzyRule08);
    FuzzyRule *fuzzyRule09 = new FuzzyRule(9, ifXbackAndYright, thenTiltLeft);
    fuzzy->addFuzzyRule(fuzzyRule09);
}

FUZZY_OUTPUT getFuzzyOutput(float input_x, float input_y)
{
    input_x = input_x * 100;
    input_y = input_y * 100;

    fuzzy->setInput(1, input_x);
    fuzzy->setInput(2, input_y);
    fuzzy->fuzzify();
    tempFuzzyOutput.left_position = fuzzy->defuzzify(1);
    tempFuzzyOutput.right_position = fuzzy->defuzzify(2);
    return tempFuzzyOutput;
}