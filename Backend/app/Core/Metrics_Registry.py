from prometheus_client import Gauge

temperature_metric = Gauge(
    "esp32_temperature_celsius",
    "Temperature reported by ESP32"
)


heap_metric = Gauge(
    "esp32_free_heap_bytes",
    "Free heap memory of ESP32"
)

mqtt_connected = Gauge(
    "mqtt_broker_connected",
    "1 if the MQTT broker connection is active, 0 otherwise",
)

min_free_heap_metric = Gauge(
    "esp32_min_free_heap_bytes",
    "Minimum free heap since last reboot"
)
heap_fragmentation_metric = Gauge(
    "esp32_heap_fragmentation_percent",
    "Heap fragmentation percentage (0-100)"
)
cpu_freq_metric = Gauge(
    "esp32_cpu_freq_mhz",
    "CPU frequency in MHz"
)
wifi_rssi_metric = Gauge(
    "esp32_wifi_rssi_dbm",
    "WiFi signal strength in dBm"
)