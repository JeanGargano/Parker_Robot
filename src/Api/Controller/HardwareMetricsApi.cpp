#include <Arduino.h>
#include <WiFi.h>
#include "esp_system.h"
#include "../Interface/HardwareMetricsApi.h"

RTC_DATA_ATTR int bootCount = 0;

HardwareMetricsApi::HardwareMetricsApi(MqttService* mqttService) {
    this->mqtt = mqttService;
}

void HardwareMetricsApi::begin() {
    bootCount++;
    Serial.println("Hardware Metrics API started");
    Serial.printf("Boot count: %d | Reset reason: %d\n", bootCount, esp_reset_reason());
}

void HardwareMetricsApi::publishAllMetrics() {

    uint32_t freeHeap     = ESP.getFreeHeap();
    uint32_t maxBlock     = ESP.getMaxAllocHeap();
    int      fragmentation = (maxBlock > 0) ? (100 - (maxBlock * 100 / freeHeap)) : 0;

    String payload = "{";

    payload += "\"temperature\":"        + String(temperatureRead(), 2)    + ",";
    payload += "\"free_heap\":"          + String(freeHeap)                 + ",";
    payload += "\"min_free_heap\":"      + String(ESP.getMinFreeHeap())     + ",";
    payload += "\"heap_fragmentation\":" + String(fragmentation)            + ",";
    payload += "\"cpu_freq_mhz\":"       + String(ESP.getCpuFreqMHz())      + ",";
    payload += "\"wifi_rssi\":"          + String(WiFi.RSSI());
    payload += "}";

    mqtt->publish("esp32/metrics", payload);
}