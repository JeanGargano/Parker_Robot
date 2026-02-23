#ifndef LOCOMOTION_SYSTEM_H
#define LOCOMOTION_SYSTEM_H

#include "Leg.h"

class LocomotionSystem {
private:
    Leg leg;

public:
    LocomotionSystem(int servoPin);
    void init();
    void move(int angle);
};

#endif
