#include "../Interface/MqttService.h"
#include <Arduino.h>

MqttService::MqttService(PubSubClient& mqttClient, WiFiService& wifiService)
    : client(mqttClient), wifi(wifiService), broker(nullptr), port(1883) {}

void MqttService::begin(const char* brokerAddr, int brokerPort, const char* id) {
    broker = brokerAddr;
    port = brokerPort;

    // Genera un clientId único usando el MAC address si no se proporciona uno
    if (id != nullptr) {
        clientId = String(id);
    } else {
        clientId = "esp32_" + String((uint32_t)ESP.getEfuseMac(), HEX);
    }

    client.setServer(broker, port);
    reconnect();
}

void MqttService::reconnect() {
    int attempts = 0;
    while (!client.connected() && attempts < 5) {
        Serial.printf("Conectando a MQTT [%s:%d] con id '%s'...\n",
                      broker, port, clientId.c_str());

        bool connected = client.connect(clientId.c_str());

        if (connected) {
            Serial.println("MQTT conectado");
            return;
        }

        Serial.printf("Fallo, rc=%d. Reintentando en 3s...\n", client.state());
        delay(3000);
        attempts++;
    }

    if (!client.connected()) {
        Serial.println("No se pudo conectar a MQTT después de 5 intentos.");
    }
}

bool MqttService::publish(const char* topic, const String& payload) {
    if (!client.connected()) {
        Serial.println("MQTT desconectado, no se puede publicar.");
        return false;
    }
    bool ok = client.publish(topic, payload.c_str());
    if (!ok) {
        Serial.printf("Error al publicar en topic: %s\n", topic);
    }
    return ok;
}

bool MqttService::isConnected() const {
    return client.connected();
}

void MqttService::loop() {
    wifi.reconnectIfNeeded();

    if (!client.connected()) {
        reconnect();
    }

    client.loop();
}