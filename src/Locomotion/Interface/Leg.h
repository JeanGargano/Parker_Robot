#ifndef LEG_H
#define LEG_H

#include "Motor.h"

class Leg {
private:
    Motor motor;

public:
    Leg(int pin);
    void init();
    void moveTo(int angle);
};

#endif
