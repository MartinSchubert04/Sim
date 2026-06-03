#pragma once

#include "pch.h"
#include "Planet.h"
#include "Universe.h"

class CameraController {

public:
    CameraController() = default;
    void update(Camera3D &camera);

private:
    void handleMovement(Camera3D &camera);
    void handleZoom(Camera3D &camera);
    void handlePlanetSelection(Camera3D &camera);
    Vector2 getTouchDelta();
    Vector2 getTouch();


private:
    Vector2 _lastPos = {0.f, 0.f};
    b32 _touching = false;
    float _lastPinchDist;
    Planet *_planetFocus = nullptr;
};
