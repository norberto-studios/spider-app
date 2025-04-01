from fastapi import FastAPI, WebSocket
import pybullet as p
import time
import asyncio

app = FastAPI()

# Connect to PyBullet in Direct mode (no GUI)
p.connect(p.DIRECT)

# # Load OBJ model into simulation
# collisionShapeId = p.createCollisionShape(p.GEOM_MESH, fileName="your_model.obj")
# visualShapeId = p.createVisualShape(p.GEOM_MESH, fileName="your_model.obj")
# objId = p.createMultiBody(baseMass=1, baseCollisionShapeIndex=collisionShapeId, baseVisualShapeIndex=visualShapeId,
#                           basePosition=[0, 0, 1])


@app.get("/")
async def root():
    return {"message": "3D Simulation API Running"}


# @app.websocket("/ws")
# async def websocket_endpoint(websocket: WebSocket):
#     await websocket.accept()
#     while True:
#         # Simulate physics step
#         p.stepSimulation()
#         pos, orn = p.getBasePositionAndOrientation(objId)
#
#         # Send position to frontend
#         await websocket.send_json({"position": pos, "orientation": orn})
#         await asyncio.sleep(1 / 60)  # 60 FPS


