#include "../Interface/CommandInterpreter.h"
#include <Arduino.h>

Command CommandInterpreter::interpret(int joystickValue) {
    Command cmd;

    int angle = map(joystickValue, -128, 127, 0, 180);

    cmd.servoAngle = angle;

    return cmd;
}
