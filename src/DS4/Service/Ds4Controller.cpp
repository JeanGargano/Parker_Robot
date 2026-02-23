#include "ps4Controller.h"
#include "../Interface/Ds4Controller.h"

void Ds4Controller::init() {
    if (!PS4.begin("14:33:5c:52:71:0a")) {
        Serial.println("Error: No se pudo inicializar el Bluetooth.");
    } else {
        Serial.println("Bluetooth listo. Esperando al DualShock 4");
    }
}

void Ds4Controller::chekConnection() {
    if (PS4.isConnected()) {
        Serial.println("¡Control DS4 Conectado exitosamente!");
        PS4.setLed(0, 0, 255); 
        PS4.sendToController();
    } else {
        Serial.println("Esperando conexión del control...");
    }
}

int Ds4Controller::readInput() {
    if (PS4.isConnected()) {
        return PS4.LStickY();
    }
    return 0;
}
    