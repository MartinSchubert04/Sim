#pragma once

#include "pch.h"
#include "DeltaTime.h"

class Planet {

public:
    Vector3 _pos;
    float _radius;
    float _mass;
    Color _color;

    Planet(Vector3 pos, float radius, float mass, Texture texture, Color color = RAYWHITE);
    ~Planet();

    void update(DeltaTime dt);
    void draw();

private:
    Model _model;
    Material _material;
    float _rotationAngle = 0.f;

};
