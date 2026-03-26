#include "../Interface/CommandInterpreter.h"
#include <Arduino.h>

Command CommandInterpreter::interpret(char input) {

    Command cmd;

    switch(input) {


        case 'S':
            cmd.type = STAND;
            break;

        case 'C':
            cmd.type = SIT;
            break;
        case 'D':
            cmd.type = STAND_DIAGONAL;
            break;

        case 'H':
            cmd.type = HELLO;
            break;

        case 'W':
            cmd.type = WALK;
            break;

        default:
            cmd.type = UNKNOWN;
    }

    return cmd;
}
