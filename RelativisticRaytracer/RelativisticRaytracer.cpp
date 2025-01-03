// RelativisticRaytracer.cpp : Defines the entry point for the application.
//

#include "RelativisticRaytracer.h"
#include "Graphics/TracingEngine.h"

#include <raymath.h>
#include <raylib.h>

using namespace std;

int main()
{
	InitWindow(2048, 1024, "raylib raytracer");
	SetTargetFPS(80);

	float deltaTime = 0;

	Camera camera = Camera();
	camera.position = Vector3(15, 8, 15);
	camera.target = Vector3(0, 0.5f, 0);
	camera.up = Vector3(0, 1, 0);
	camera.fovy = 45;
	camera.projection = CAMERA_PERSPECTIVE;

	DisableCursor();

	TracingEngine::Initialize(Vector2(2048, 1024), 7, 10, 0.001f);

	TracingEngine::skyMaterial = SkyMaterial{ DARKGRAY, DARKGRAY, DARKGRAY, DARKGRAY, Vector3(-0.5f, -1, -0.5f), 1, 0.5 };

	RaytracingMaterial red = { Vector4(1,1,1,1), Vector4(1,0,0,10), Vector4(0,0,0,0) };
	RaytracingMaterial red2 = { Vector4(1,0.6f,0.6f,0), Vector4(0,0,0,0), Vector4(0,0,0,0) };
	RaytracingMaterial green = { Vector4(1,1,1,1), Vector4(0,0,1,10), Vector4(0,0,0,0) };
	RaytracingMaterial blue = { Vector4(1,1,1,1), Vector4(0,1,0,10), Vector4(0,0,0,0) };
	RaytracingMaterial white = { Vector4(1,1,1,1), Vector4(0,0,0,0), Vector4(0,0,0,0) };
	RaytracingMaterial grey = { Vector4(0.5f,0.5f,0.5f,1), Vector4(0,0,0,0), Vector4(0,0,0,0) };
	RaytracingMaterial light = { Vector4(1,0.6f,0.6f,1), Vector4(1,0.8,0.6,1.5), Vector4(0,0,0,0) };
	RaytracingMaterial metal = { Vector4(1,1,1,1), Vector4(0,0,0,0), Vector4(0,1,0,0) };

	TracingEngine::gravityBodies.push_back({ {0,5,0,10} });

	Model model = LoadModel("resources/meshes/monkey.obj");
	model.transform = MatrixTranslate(0, 3, 0);
	TracingEngine::UploadRaylibModel(model, red2, false, 8);

	Model ring = LoadModelFromMesh(GenMeshTorus(1, 4.0f, 16, 32));
	ring.transform = MatrixScale(1, 1, 0.1f) * MatrixRotateX(PI / 2) * MatrixTranslate(0, 5, 0);
	TracingEngine::UploadRaylibModel(ring, light, false, 10);

	TracingEngine::UploadStaticData();

	while (!WindowShouldClose())
	{
		UpdateCamera(&camera, CAMERA_FREE);


		TracingEngine::UploadData(&camera);

		if (IsKeyPressed(KEY_ONE)) TracingEngine::debug = !TracingEngine::debug;
		if (IsKeyPressed(KEY_R)) TracingEngine::denoise = !TracingEngine::denoise;
		if (IsKeyPressed(KEY_P)) TracingEngine::pause = !TracingEngine::pause;

		TracingEngine::Render(&camera);

		deltaTime += GetFrameTime();
	}

	UnloadModel(model);
	UnloadModel(ring);

	TracingEngine::Unload();

	CloseWindow();
}

