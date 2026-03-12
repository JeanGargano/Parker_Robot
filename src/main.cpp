#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include "Api/Interface/WiFiService.h"
#include "Api/Interface/MqttService.h"
#include "Api/Interface/HardwareMetricsApi.h"


#define WIFI_SSID           "TuRedWiFi"
#define WIFI_PASSWORD       "TuPassword"
#define MQTT_BROKER         "192.168.1.100"
#define MQTT_PORT           1883
#define PUBLISH_INTERVAL_MS 5000

WiFiClient  wifiClient;
PubSubClient mqttClient(wifiClient);

WiFiService         wifiService(WIFI_SSID, WIFI_PASSWORD);
MqttService         mqttService(mqttClient, wifiService);
HardwareMetricsApi  metrics(&mqttService);

unsigned long lastPublish = 0;

void setup() {
    Serial.begin(115200);

    wifiService.connect();
    mqttService.begin(MQTT_BROKER, MQTT_PORT);
    metrics.begin();
}

void loop() {
    mqttService.loop();

    unsigned long now = millis();
    if (now - lastPublish >= PUBLISH_INTERVAL_MS) {
        lastPublish = now;
        metrics.publishAllMetrics();
    }
}