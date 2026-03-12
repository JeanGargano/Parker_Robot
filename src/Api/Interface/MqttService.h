#ifndef MQTT_SERVICE_H
#define MQTT_SERVICE_H

#include <PubSubClient.h>
#include "WiFiService.h"

class MqttService {
private:
    PubSubClient& client;
    WiFiService& wifi;
    const char* broker;
    int port;
    String clientId;

    void reconnect();

public:
    MqttService(PubSubClient& mqttClient, WiFiService& wifiService);

    void begin(const char* broker, int port, const char* clientId = nullptr);
    bool publish(const char* topic, const String& payload);
    bool isConnected() const;
    void loop();
};

#endif