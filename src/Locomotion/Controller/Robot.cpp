#include "../Interface/Robot.h"

Robot::Robot(
    int r1, int r2, int l1, int l2,
    int r3, int r4, int l3, int l4,
    CommandInterpreter & cmd
)
: locomotion(r1, r2, l1, l2, r3, r4, l3, l4),
  interpreter(cmd)
{
}

void Robot::init() {
    locomotion.init();
}

void Robot::executeCommand(Command cmd) {

    switch(cmd.type) {


        case STAND:
            Serial.println("Comando STAND recibido");
            locomotion.stand();
            break;


        case SIT:
            Serial.println("Comando SIT recibido");
            locomotion.sit();
            break;


        default:
            Serial.println("Comando desconocido");
    }

}