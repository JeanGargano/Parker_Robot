from pydantic import BaseModel


class SensorMetrics(BaseModel):
    temperature: float
    humidity: float
    free_heap: int
    wifi_rssi: int
