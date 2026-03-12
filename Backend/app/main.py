from fastapi import FastAPI

from app.controllers.metrics_controller import router as metrics_router
from app.services.mqtt_service import MQTTService


app = FastAPI()

mqtt_service = MQTTService()


@app.on_event("startup")
def startup():

    mqtt_service.connect()


app.include_router(metrics_router)
