#ifndef ROBOT_H
#define ROBOT_H

#include "LocomotionSystem.h"
#include "../../Command/Interface/Command.h"
#include "../../Command/Interface/CommandInterpreter.h"

class Robot {
private:
    LocomotionSystem locomotion;
    CommandInterpreter& interpreter;

public:
    Robot(int servoPin, CommandInterpreter& cmd);
    void init();
    void executeCommand(Command cmd);
};

#endif
