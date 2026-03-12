from fastapi import APIRouter
from prometheus_client import generate_latest
from fastapi.responses import Response


router = APIRouter()


@router.get("/metrics")
def metrics():

    data = generate_latest()

    return Response(
        content=data,
        media_type="text/plain"
    )
