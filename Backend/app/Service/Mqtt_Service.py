import json
import time
import threading

import paho.mqtt.client as mqtt
from pydantic import ValidationError

from app.Config.Settings import settings
from app.Core.Logger import get_logger
from app.Model.Sensor_Metrics import SensorMetrics
from app.Core.Metrics_Registry import (
    temperature_metric,
    heap_metric,
    mqtt_connected,
    min_free_heap_metric,
    heap_fragmentation_metric,
    cpu_freq_metric,
)

logger = get_logger(__name__)


class MQTTService:

    def __init__(self) -> None:
        self.broker = settings.mqtt_broker
        self.port = settings.mqtt_port
        self.topic = settings.mqtt_topic
        self._reconnect_delay = settings.mqtt_reconnect_delay
        self._max_attempts = settings.mqtt_max_reconnect_attempts
        self._stop_event = threading.Event()
        self.client = mqtt.Client(client_id="esp32-metrics-api", clean_session=True)
        self.client.on_connect = self._on_connect
        self.client.on_disconnect = self._on_disconnect
        self.client.on_message = self._on_message
        mqtt_connected.set(0)


    def connect(self) -> None:
        """Inicia la conexión con reintentos en hilo separado."""
        thread = threading.Thread(target=self._connect_with_retry, daemon=True)
        thread.start()

    def disconnect(self) -> None:
        """Cierra la conexión limpiamente."""
        logger.info("Cerrando conexión MQTT...")
        self._stop_event.set()
        self.client.loop_stop()
        self.client.disconnect()
        mqtt_connected.set(0)
        logger.info("Conexión MQTT cerrada.")

    def _connect_with_retry(self) -> None:
        attempt = 0
        while not self._stop_event.is_set():
            attempt += 1
            try:
                logger.info(
                    "Conectando a MQTT broker %s:%s (intento %d/%d)...",
                    self.broker, self.port, attempt, self._max_attempts,
                )
                self.client.connect(self.broker, self.port, keepalive=60)
                self.client.loop_start()
                return

            except Exception as exc:
                logger.error("Error al conectar: %s", exc)
                mqtt_connected.set(0)

                if attempt >= self._max_attempts:
                    logger.critical(
                        "Se alcanzó el máximo de intentos (%d). Deteniendo reintentos.",
                        self._max_attempts,
                    )
                    return

                logger.info("Reintentando en %ds...", self._reconnect_delay)
                self._stop_event.wait(self._reconnect_delay)


    def _on_connect(self, client: mqtt.Client, userdata, flags, rc: int) -> None:
        if rc == 0:
            logger.info("Conectado al broker. Suscribiendo a '%s'.", self.topic)
            client.subscribe(self.topic)
            mqtt_connected.set(1)
        else:
            logger.error("Conexión rechazada por el broker. Código: %d", rc)
            mqtt_connected.set(0)

    def _on_disconnect(self, client: mqtt.Client, userdata, rc: int) -> None:
        mqtt_connected.set(0)
        if rc == 0:
            logger.info("Desconectado limpiamente del broker.")
        else:
            logger.warning(
                "Desconexión inesperada (rc=%d). Paho intentará reconectar.", rc
            )

    def _on_message(self, client: mqtt.Client, userdata, msg: mqtt.MQTTMessage) -> None:
        raw = msg.payload.decode(errors="replace")

        try:
            payload = json.loads(raw)
            logger.info("Mensaje recibido en '%s': %s", msg.topic, payload)
        except json.JSONDecodeError as exc:
            logger.warning("JSON inválido recibido: %s | Error: %s", raw, exc)
            return

        try:
            data = SensorMetrics(**payload)
        except (ValidationError, TypeError) as exc:
            logger.warning("Payload no cumple el modelo: %s | Error: %s", payload, exc)
            return

        self._update_metrics(data)
        logger.debug("Métricas actualizadas: %s", data.model_dump())

    def _update_metrics(self, data: SensorMetrics) -> None:
        temperature_metric.set(data.temperature)
        heap_metric.set(data.free_heap)
        min_free_heap_metric.set(data.min_free_heap)
        heap_fragmentation_metric.set(data.heap_fragmentation)
        cpu_freq_metric.set(data.cpu_freq_mhz)