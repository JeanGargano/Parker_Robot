from fastapi import APIRouter
from fastapi.responses import Response, JSONResponse
from prometheus_client import generate_latest, CONTENT_TYPE_LATEST

router = APIRouter()


@router.get("/metrics", summary="Prometheus metrics scrape endpoint")
def metrics() -> Response:
    return Response(
        content=generate_latest(),
        media_type=CONTENT_TYPE_LATEST,
    )


@router.get("/health", summary="Liveness probe")
def health() -> JSONResponse:
    return JSONResponse(content={"status": "ok"})