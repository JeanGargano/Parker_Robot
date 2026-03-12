# Correr sevidor Backend FastApi
uvicorn app.main:app --reload
# Ver logs del broker dentro del container
docker exec -it <nombre_del_contenedor> sh