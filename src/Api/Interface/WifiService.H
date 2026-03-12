#ifndef WIFI_SERVICE_H
#define WIFI_SERVICE_H

class WiFiService {
private:
    const char* ssid;
    const char* password;

public:
    WiFiService(const char* ssid, const char* password);

    void connect();
    void reconnectIfNeeded();
    bool isConnected() const;
};

#endif