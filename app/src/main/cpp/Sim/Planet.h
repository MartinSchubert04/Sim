#pragma once

#include "pch.h"

class Planet {

public:
  Vector3 _pos;
  float _radius;
  float _mass;
  Color _color;

  Planet(Vector3 pos, float radius, float mass, Texture texture, Color color = RAYWHITE);

  void update();
  void draw();

private:
    Mesh _mesh;
    Material _material;

};
