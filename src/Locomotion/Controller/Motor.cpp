#include "../Interface/Motor.h"

Motor::Motor(int pin) : pin(pin), currentAngle(-1), attached(false) {}

void Motor::attach() {
    if (!attached) {
        servo.attach(pin);
        attached = true;
    }
}

void Motor::setAngle(int angle) {
    int correctedAngle = angle;

    //if (correctedAngle < 0) correctedAngle = 0;
    //if (correctedAngle > 180) correctedAngle = 180;

    currentAngle = correctedAngle;

    if (attached) {
        servo.write(correctedAngle);
    }
}

int Motor::getAngle() {
    return currentAngle;
}
