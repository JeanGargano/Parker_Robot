from prometheus_client import Gauge

temperature_metric = Gauge(
    "esp32_temperature_celsius",
    "Temperature reported by ESP32"
)

humidity_metric = Gauge(
    "esp32_humidity_percent",
    "Humidity reported by ESP32"
)

heap_metric = Gauge(
    "esp32_free_heap_bytes",
    "Free heap memory of ESP32"
)

wifi_metric = Gauge(
    "esp32_wifi_rssi_dbm",
    "WiFi signal strength"
)
