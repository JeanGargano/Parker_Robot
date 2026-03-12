#ifndef COMMAND_H
#define COMMAND_H

enum CommandType {
    STAND,
    SIT,
    HELLO,
    WALK,
    UNKNOWN
};

struct Command {
    CommandType type;
};

#endif
