#include "../Interface/Foot.h"

Foot::Foot(int pin) : motor(pin) {}

void Foot::init() {
    motor.attach();
}

void Foot::moveTo(int angle) {
    motor.setAngle(angle);
}
