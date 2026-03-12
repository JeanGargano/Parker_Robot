#ifndef LOCOMOTION_SYSTEM_H
#define LOCOMOTION_SYSTEM_H

#include "Leg.h"
#include "Foot.h"

class LocomotionSystem {
private:
    Leg R1;
    Leg R2;
    Leg L1;
    Leg L2;
    Foot R3;
    Foot R4;
    Foot L3;
    Foot L4;

public:
    LocomotionSystem(
        int r1, int r2, int l1, int l2,
        int r3, int r4, int l3, int l4
    );

    void init();
    void stand();
    void sit();

};

#endif
