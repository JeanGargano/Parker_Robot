from pydantic_settings import BaseSettings


class Settings(BaseSettings):

    # MQTT
    mqtt_broker: str
    mqtt_port: int
    mqtt_topic: str

    # API
    api_host: str
    api_port: int

    class Config:
        env_file = ".env"
        env_file_encoding = "utf-8"


settings = Settings()
