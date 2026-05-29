#include "Application.h"
#include "CameraController.h"
#include "Planet.h"

Application *Application::instance = nullptr;

Application *createApplication() { return new Application();}

Application::Application() {
    instance = this;

    InitWindow(0,0, "Pong");
    InitAudioDevice();
    InitSensorManager();
    EnableSensor(SENSOR_ACCELEROMETER);

    _window = {(float)GetScreenWidth(), (float)GetScreenHeight()};
}


void Application::run() {
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };  // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                          // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                       // Camera mode type

    auto cameraController = CameraController();

    Texture t = LoadTexture("textures/earth/colormap.jpg");
    auto planet = Planet({0,0,0}, .5f, 1.f, t);

    while(!WindowShouldClose()) {
        auto time = (float)GetTime();
        dt = time - _lastTime;
        _lastTime = time;

        BeginDrawing();
          BeginMode3D(camera);

            // updates
            cameraController.update(camera);

            // draw
            DrawGrid(10, 1.0f);
            planet.draw();


            DrawText("Hello world", (int)(_window.x / 2/ 2), _window.y / 2, 20, {245, 245, 245, 80});

          EndMode3D();
        EndDrawing();
    }
}