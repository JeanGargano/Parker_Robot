#include "../Interface/WifiService.H"
#include <Arduino.h>
#include <WiFi.h>

WiFiService::WiFiService(const char* ssid, const char* password)
    : ssid(ssid), password(password) {}

void WiFiService::connect() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.printf("Conectando a WiFi '%s'", ssid);

    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED) {
        if (millis() - start > 15000) {
            Serial.println("\nTimeout de WiFi. Reiniciando...");
            ESP.restart();
        }
        delay(500);
        Serial.print(".");
    }

    Serial.printf("\nWiFi conectado — IP: %s\n", WiFi.localIP().toString().c_str());
}

void WiFiService::reconnectIfNeeded() {
    if (WiFi.status() == WL_CONNECTED) return;

    Serial.println("WiFi desconectado. Reconectando...");
    WiFi.reconnect();

    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < 10000) {
        delay(500);
        Serial.print(".");
    }

    if (isConnected()) {
        Serial.printf("\nWiFi reconectado — IP: %s\n", WiFi.localIP().toString().c_str());
    } else {
        Serial.println("\nNo se pudo reconectar al WiFi.");
    }
}

bool WiFiService::isConnected() const {
    return WiFi.status() == WL_CONNECTED;
}