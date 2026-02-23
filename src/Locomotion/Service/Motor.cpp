#include "../Interface/Motor.h"

Motor::Motor(int pin) {
    this->pin = pin;
    this->currentAngle = 90;
}

void Motor::attach() {
    servo.attach(pin);
    servo.write(currentAngle);
}

void Motor::setAngle(int angle) {
    if (angle < 0) angle = 0;
    if (angle > 180) angle = 180;

    currentAngle = angle;
    servo.write(angle);
}

int Motor::getAngle() {
    return currentAngle;
}
