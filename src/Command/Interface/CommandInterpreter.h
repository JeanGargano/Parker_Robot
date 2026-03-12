#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H

#include "Command.h"

class CommandInterpreter {
public:
    Command interpret(char input);
};

#endif
