#ifndef FOOT_H
#define FOOT_H

#include "Motor.h"

class Foot {
private:
    Motor motor;

public:
    Foot(int pin);
    void init();
    void moveTo(int angle);
};

#endif
