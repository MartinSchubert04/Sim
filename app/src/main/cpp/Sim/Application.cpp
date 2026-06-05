#include "Application.h"
#include "CameraController.h"
#include "Planet.h"
#include "Renderer.h"
#include "Global.h"
#include "Universe.h"
#include "rlgl.h"

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

    // Camera setup
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 80.0f };  // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                          // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                       // Camera mode type

    rlSetClipPlanes(1.f, 40000.0);

    auto cameraController = CameraController();

    // System setup
    Universe universe;

    universe.setStar({
      .name = "Sun",
      .pos = {0,0,0},
      .radius = 10.f,
      .mass = 100.f,
      .colorMap = LoadTexture("textures/sun/sunmap.jpg"),
      .isStar = true
    });

    universe.add({
      .name = "Earth",
      .pos  = {0, 0, -15.5f},
      .radius = 1.f,
      .mass = 1.f,
      .colorMap    = LoadTexture("textures/earth/colormap.png"),
      .specularMap = LoadTexture("textures/earth/specularmap.jpg"),
      .nightMap    = LoadTexture("textures/earth/nightmap.jpg")
    });


    while(!WindowShouldClose()) {
        auto time = (float)GetTime();
        dt = time - _lastTime;
        _lastTime = time;

        BeginDrawing();
          ClearBackground(BLACK);
          BeginMode3D(camera);

            // updates
            cameraController.update(camera);
            universe.update(dt);

            // draw
            Renderer::drawGrid({0, -12.f, 0}, 40, 2.0f, 0.2f, 1.f);
            universe.draw(camera.position);

          EndMode3D();

          // text camera fixed
//          Renderer::drawLabel("X", {2.2f,0,0}, 25.f, camera, RED);
//          Renderer::drawLabel("Y", {0,2.2f,0}, 25.f, camera, GREEN);
//          Renderer::drawLabel("Z", {0,0,2.2f}, 25.f, camera, BLUE);

          auto e = universe.getEntity("Earth");
          Renderer::drawLabel(e->_name.c_str(), Vector3Add(e->_pos, {0,e->_radius + e->_radius *.4f,0}), 35.f, camera, RAYWHITE);

          auto s = universe.getStar();
          Renderer::drawLabel(s->_name.c_str(), Vector3Add(s->_pos, {0,s->_radius + s->_radius *.2f,0}), 35.f, camera, RAYWHITE);

          DrawText(std::to_string(GetFPS()).c_str(), 50, 30, 40, RAYWHITE);

      EndDrawing();
    }
}