from pydantic import BaseModel


class SensorMetrics(BaseModel):
    temperature: float
    free_heap: int
    wifi_rssi: int
    uptime: int
    min_free_heap: int
    heap_fragmentation: int
    cpu_freq_mhz: int
    wifi_channel: int
    boot_count: int
    reset_reason: int
