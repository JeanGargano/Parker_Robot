#ifndef ROBOT_H
#define ROBOT_H

#include "LocomotionSystem.h"
#include "../../Command/Interface/Command.h"
#include "../../Command/Interface/CommandInterpreter.h"

class Robot {
private:
    LocomotionSystem locomotion;
    CommandInterpreter & interpreter;

public:
    Robot(
        int r1, int r2, int l1, int l2,
        int r3, int r4, int l3, int l4,
        CommandInterpreter & cmd
    );

    void init();
    void executeCommand(Command cmd);
};

#endif
