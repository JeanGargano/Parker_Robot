from pydantic import BaseModel


class SensorMetrics(BaseModel):
    temperature: float
    free_heap: int
    min_free_heap: int
    heap_fragmentation: int
    cpu_freq_mhz: int
    wifi_rssi: int