#include "./DS4/Interface/Ds4Controller.h"
#include "./Command/Interface/CommandInterpreter.h"
#include "./Locomotion/Interface/Robot.h"

#define SERVO_PIN 2

Ds4Controller Ds4;
CommandInterpreter interpreter;
Robot robot(SERVO_PIN, interpreter);

void setup() {
    Serial.begin(115200);
    robot.init();
    Ds4.init();
}

void loop() {
    Ds4.chekConnection();

    int input = Ds4.readInput();

    Command cmd = interpreter.interpret(input);
    robot.executeCommand(cmd);

    delay(2000); 
}

