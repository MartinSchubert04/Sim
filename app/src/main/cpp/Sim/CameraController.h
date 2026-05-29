#pragma once

#include "pch.h"

class CameraController {

public:
    CameraController() = default;
    void update(Camera3D &camera);

private:
    void handleMovement(Camera3D &camera);
    void handleZoom(Camera3D &camera);
    Vector2 getTouchDelta();


private:
    Vector2 _lastPos = {0.f, 0.f};
    b32 _touching = false;
    float _lastPinchDist;
};
