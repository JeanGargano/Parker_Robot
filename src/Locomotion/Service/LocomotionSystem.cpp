#include "../Interface/LocomotionSystem.h"

LocomotionSystem::LocomotionSystem(int servoPin)
    : leg(servoPin) {}

void LocomotionSystem::init() {
    leg.init();
}

void LocomotionSystem::move(int angle) {
    leg.moveTo(angle);
}
