#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include "Api/Interface/WiFiService.h"
#include "Api/Interface/MqttService.h"
#include "Api/Interface/HardwareMetricsApi.h"
#include "Locomotion/Interface/Robot.h"

// Configuración
#define WIFI_SSID           "Jean"
#define WIFI_PASSWORD       "basket2004"
#define MQTT_BROKER         "10.88.127.161"
#define MQTT_PORT           1884
#define PUBLISH_INTERVAL_MS 5000

// Pines motores — lado derecho
#define R1_PIN 13
#define R2_PIN 12
#define R3_PIN 25
#define R4_PIN 33

// Pines motores — lado izquierdo
#define L1_PIN 14
#define L2_PIN 27
#define L3_PIN 26
#define L4_PIN 19

// API de métricas
WiFiClient   wifiClient;
PubSubClient mqttClient(wifiClient);
WiFiService        wifiService(WIFI_SSID, WIFI_PASSWORD);
MqttService        mqttService(mqttClient, wifiService);
HardwareMetricsApi metrics(&mqttService);

// Locomoción
CommandInterpreter interpreter;
Robot robot(
    R1_PIN, R2_PIN, L1_PIN, L2_PIN,
    R3_PIN, R4_PIN, L3_PIN, L4_PIN,
    interpreter
);

unsigned long lastPublish = 0;

void setup() {
    Serial.begin(115200);
    wifiService.connect();
    mqttService.begin(MQTT_BROKER, MQTT_PORT);
    metrics.begin();
    robot.init();
}

void loop() {
    // Métricas
    mqttService.loop();

    unsigned long now = millis();
    if (now - lastPublish >= PUBLISH_INTERVAL_MS) {
        lastPublish = now;
        metrics.publishAllMetrics();
    }

    // Locomoción
    if (Serial.available()) {
        char input = Serial.read();
        Serial.print("Comando recibido: ");
        Serial.println(input);

        Command cmd = interpreter.interpret(input);
        robot.executeCommand(cmd);
    }
}