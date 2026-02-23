#ifndef MOTOR_H
#define MOTOR_H

#include <ESP32Servo.h>

class Motor {
private:
    Servo servo;
    int pin;
    int currentAngle;

public:
    Motor(int pin);
    void attach();
    void setAngle(int angle);
    int getAngle();
};

#endif
