from pydantic_settings import BaseSettings
from pydantic import field_validator


class Settings(BaseSettings):

    mqtt_broker: str
    mqtt_port: int = 1884
    mqtt_topic: str
    api_host: str = "0.0.0.0"
    api_port: int = 8000
    mqtt_reconnect_delay: int = 5  
    mqtt_max_reconnect_attempts: int = 10

    log_level: str = "INFO"

    @field_validator("mqtt_port", "api_port")
    @classmethod
    def port_must_be_valid(cls, v: int) -> int:
        if not (1 <= v <= 65535):
            raise ValueError(f"Puerto inválido: {v}")
        return v

    class Config:
        env_file = ".env"
        env_file_encoding = "utf-8"


settings = Settings()