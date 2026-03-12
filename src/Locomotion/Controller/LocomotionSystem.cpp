    // LocomotionSystem.cpp

    #include "../Interface/LocomotionSystem.h"
    #include <Arduino.h>


   LocomotionSystem::LocomotionSystem(
    int r1, int r2, int l1, int l2,
    int r3, int r4, int l3, int l4
) : 
    R1(r1),
    R2(r2),
    L1(l1),
    L2(l2),
    R3(r3),
    R4(r4),
    L3(l3),
    L4(l4)
{}

    void LocomotionSystem::init() {
        R1.init();
        R2.init();
        L1.init();
        L2.init();
        R3.init();
        R4.init();
        L3.init();
        L4.init();
    }


    void LocomotionSystem::stand() {
        L3.moveTo(80);
        L4.moveTo(90);
        R3.moveTo(90);
        R4.moveTo(35);
        
    }

    void LocomotionSystem::sit() {
        L3.moveTo(180);
        L4.moveTo(0);
        R3.moveTo(0);
        R4.moveTo(130);

        // Implementa tu lógica de caminata aquí
    }