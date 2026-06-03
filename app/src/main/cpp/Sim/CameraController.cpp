#include "CameraController.h"

void CameraController::update(Camera3D &camera) {
  if (_planetFocus != nullptr)
    camera.target = _planetFocus->_pos;

  if (GetTouchPointCount() == 0) {
    _touching = false;
    _lastPinchDist = 0.f;
    return;
  }

  if (GetTouchPointCount() >= 2) {
    _touching = false;
    handleZoom(camera);
    return;
  }

  if (GetTouchPointCount() > 0) {
    if (!_touching) {
      handlePlanetSelection(camera);
    }
  }

  handleMovement(camera);
  _touching = true;
}

Vector2 CameraController::getTouch() { return {(float)GetTouchX(), (float)GetTouchY() }; }
Vector2 CameraController::getTouchDelta() {
  Vector2 pos = getTouch();
  Vector2 delta = {pos.x - _lastPos.x, pos.y - _lastPos.y};
  _lastPos = pos;
  return delta;
}

void CameraController::handleMovement(Camera3D &camera) {
  Vector2 delta = getTouchDelta();

  if (_touching) {
    float angleH = delta.x * 0.005f;
    float angleV = delta.y * 0.005f;

    Vector3 offset = Vector3Subtract(camera.position, camera.target);

    offset = Vector3RotateByAxisAngle(offset, {0, 1, 0}, -angleH);

    Vector3 right = Vector3CrossProduct(offset, camera.up);
    right = Vector3Normalize(right);
    offset = Vector3RotateByAxisAngle(offset, right, angleV);

    camera.position = Vector3Add(camera.target, offset);
  }

}

void CameraController::handleZoom(Camera3D &camera) {
  if (GetTouchPointCount() < 2) {
    _lastPinchDist = 0.f;
    return;
  }

  Vector2 p1 = GetTouchPosition(0);
  Vector2 p2 = GetTouchPosition(1);

  float dist = Vector2Distance(p1, p2);

  if (_lastPinchDist != 0.f) {
    float delta = dist - _lastPinchDist;

    // Mover la cámara hacia/desde el target
    Vector3 dir = Vector3Normalize(Vector3Subtract(camera.position, camera.target));
    camera.position = Vector3Add(camera.position, Vector3Scale(dir, -delta * 0.01f));
  }

  _lastPinchDist = dist;
}

void CameraController::handlePlanetSelection(Camera3D &camera) {
  Vector2 touch = getTouch();

  Ray  ray = GetScreenToWorldRay(getTouch(), camera);

  for (auto &e : Universe::getEntities()) {
      auto collision = GetRayCollisionSphere(ray, e._pos, e._radius);
      if(collision.hit) {
        _planetFocus = &e;
        break;
      }
  }

  // check for sun
  RayCollision colSun = GetRayCollisionSphere(ray, Universe::getStar()._pos, Universe::getStar()._radius);
  if (colSun.hit) {
    _planetFocus = &Universe::getStar();
  }
}

