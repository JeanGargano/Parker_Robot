from contextlib import asynccontextmanager
from typing import AsyncGenerator

from fastapi import FastAPI

from app.Controller.Metrics_Controller import router as metrics_router
from app.Service.Mqtt_Service import MQTTService
from app.Core.Logger import get_logger

logger = get_logger(__name__)

mqtt_service = MQTTService()


@asynccontextmanager
async def lifespan(app: FastAPI) -> AsyncGenerator:
    logger.info("Iniciando servicio MQTT...")
    mqtt_service.connect()
    yield
    logger.info("Apagando servicio MQTT...")
    mqtt_service.disconnect()


app = FastAPI(
    title="ESP32 Metrics API",
    description="Recibe métricas de sensores vía MQTT y las expone en formato Prometheus.",
    version="2.0.0",
    lifespan=lifespan,
)

app.include_router(metrics_router, tags=["Observability"])