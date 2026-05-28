#pragma once

#include "pch.h"

class Planet {

public:
  Vector3 _pos;
  float _radius;
  float _mass;
  Color _color;

  Planet(Vector3 pos, float radius, float mass, Color color = RAYWHITE)
            : _pos(pos), _radius(radius), _mass(mass), _color(color) {}

  void update();
  void draw();

};
