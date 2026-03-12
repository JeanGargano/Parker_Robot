from app.config.settings import settings
import paho.mqtt.client as mqtt
from app.models.sensor_metrics import SensorMetrics
from app.core.metrics_registry import (
    temperature_metric,
    humidity_metric,
    heap_metric,
    wifi_metric
)
import json

class MQTTService:

    def __init__(self):

        self.broker = settings.mqtt_broker
        self.port = settings.mqtt_port
        self.topic = settings.mqtt_topic

        self.client = mqtt.Client()
        self.client.on_message = self.on_message

    def connect(self):
        self.client.connect(self.broker, self.port)
        self.client.subscribe(self.topic)
        self.client.loop_start()

    def on_message(self, client, userdata, msg):

        payload = json.loads(msg.payload.decode())

        data = SensorMetrics(**payload)

        temperature_metric.set(data.temperature)
        humidity_metric.set(data.humidity)
        heap_metric.set(data.free_heap)
        wifi_metric.set(data.wifi_rssi)
