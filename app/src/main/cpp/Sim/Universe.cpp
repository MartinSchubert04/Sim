#include "Universe.h"

float Universe::G = 1.0f;

void Universe::update(DeltaTime dt) {
  updateOrbits(dt);

  for (auto &e : entities) {
    e.update(dt);
  }
}

void Universe::updateOrbits(DeltaTime dt) {
  for (auto &e : entities) {

    float d = Vector3Distance(sun._pos, e._pos);

    if (d < 0.0001) d = 0.0001;

    float f = (G * sun._mass * e._mass) / (d * d);

    Vector3 dir = Vector3Normalize(Vector3Subtract(sun._pos, e._pos));

    Vector3 acc = Vector3Scale(dir, f / e._mass);

    e._speed = Vector3Add(e._speed, Vector3Scale(acc, dt.getSeconds()));
  }
}

void Universe::draw() {
  for (auto &e : entities) {
    e.draw();
  }
  sun.draw();
}
