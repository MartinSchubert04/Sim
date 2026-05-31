#include "Application.h"
#include "CameraController.h"
#include "Planet.h"
#include "Renderer.h"
#include "Global.h"

Application *Application::instance = nullptr;

Application *createApplication() { return new Application();}

Application::Application() {
    instance = this;

    InitWindow(0,0, "Pong");
    InitAudioDevice();
    InitSensorManager();
    EnableSensor(SENSOR_ACCELEROMETER);

    _window = {(float)GetScreenWidth(), (float)GetScreenHeight()};

    Global::instance().init();
}


void Application::run() {
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };  // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                          // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                       // Camera mode type

    auto cameraController = CameraController();

    Texture t = LoadTexture("textures/earth/colormap90.png");
    auto planet = Planet({0,0,0}, .5f, 1.f, t);

    while(!WindowShouldClose()) {
        auto time = (float)GetTime();
        dt = time - _lastTime;
        _lastTime = time;

        BeginDrawing();
          BeginMode3D(camera);

            // updates
            cameraController.update(camera);
            planet.update(dt);

            // draw
            DrawGrid(10, 1.0f);

            planet.draw();

            // axis x = red, y = green, blue = z
            Renderer::DrawArrow({0,0,0}, {2,0,0}, 0.01f, 0.1, 8, RED);
            Renderer::DrawArrow({0,0,0}, {0,2,0}, 0.01f, 0.1, 8, GREEN);
            Renderer::DrawArrow({0,0,0}, {0,0,2}, 0.01f, 0.1, 8, BLUE);

          EndMode3D();

          // text camera fixed
          Renderer::DrawLabel("X", {2.2f,0,0}, 25.f,camera, RED);
          Renderer::DrawLabel("Y", {0,2.2f,0}, 25.f, camera, GREEN);
          Renderer::DrawLabel("Z", {0,0,2.2f}, 25.f, camera, BLUE);

        EndDrawing();
    }
}