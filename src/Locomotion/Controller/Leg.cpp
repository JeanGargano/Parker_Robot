#include "../Interface/Leg.h"

Leg::Leg(int pin) : motor(pin) {}

void Leg::init() {
    motor.attach();
}

void Leg::moveTo(int angle) {
    motor.setAngle(angle);
}
