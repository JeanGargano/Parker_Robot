#include <Arduino.h>
#include <WiFi.h>
#include "esp_system.h"
#include "HardwareMetricsApi.h"

HardwareMetricsApi::HardwareMetricsApi(MqttService* mqttService) {
    this->mqtt = mqttService;
}

void HardwareMetricsApi::begin() {
    Serial.println("Hardware Metrics API started");
}

void HardwareMetricsApi::publishAllMetrics() {

    String payload = "{";

    payload += "\"temperature\":" + String(temperatureRead()) + ",";
    payload += "\"free_heap\":" + String(ESP.getFreeHeap()) + ",";
    payload += "\"wifi_rssi\":" + String(WiFi.RSSI()) + ",";
    payload += "\"uptime\":" + String(millis() / 1000);

    payload += "}";

    mqtt->publish("esp32/metrics", payload);
}
