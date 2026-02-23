#include "../Interface/Robot.h"

Robot::Robot(int servoPin, CommandInterpreter& cmd)
    : locomotion(servoPin), interpreter(cmd) {}

void Robot::init() {
    locomotion.init();
}

void Robot::executeCommand(Command cmd) {
    locomotion.move(cmd.servoAngle);
}
