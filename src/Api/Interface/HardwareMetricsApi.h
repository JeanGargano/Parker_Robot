#ifndef HARDWARE_METRICS_API_H
#define HARDWARE_METRICS_API_H

#include "MqttService.h"

class HardwareMetricsApi {

private:
    MqttService* mqtt;

public:
    HardwareMetricsApi(MqttService * mqttService);

    void begin();

    void publishAllMetrics();
};

#endif
