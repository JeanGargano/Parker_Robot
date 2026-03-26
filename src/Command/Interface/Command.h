#ifndef COMMAND_H
#define COMMAND_H

enum CommandType {
    STAND,
    SIT,
    STAND_DIAGONAL,
    HELLO,
    DANCE,
    EXERCISE,
    WALK,
    TURN_RIGHT,
    TURN_LEFT,
    UNKNOWN
};

struct Command {
    CommandType type;
};

#endif
