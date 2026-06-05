#pragma once

#include "pch.h"
#include "DeltaTime.h"

class PlanetSpec {
public:
    std::string  name;
    Vector3      pos;
    float        radius, mass;
    Texture      colorMap;
    Texture      specularMap;  // opcional — fallback a textura blanca 1x1
    Texture      nightMap;     // opcional — fallback a textura negra 1x1
    bool         isStar = false;
};

class Planet {

public:
    std::string _name;
    Vector3 _pos;
    float _radius;
    Vector3 _speed;
    float _mass;
    float _orbitAngle = 0.f;
    float _orbitRadius = 1.5f;
    float _orbitSpeed = 1.f;
    bool _isStar;

    Planet() = default;
    Planet(std::string name, Vector3 pos, float radius, float mass, std::vector<Texture> textures, bool isStar);
    ~Planet();

    void update(DeltaTime dt);
    void draw(Vector3 lightPos, Vector3 camPos);

private:
    void orbit(DeltaTime dt);

private:
    Model  _model;
    Shader _shader;
    float  _rotationAngle = 0.f;

    int _lightPosLoc = -1;
    int _camPosLoc   = -1;
    int _isStarLoc   = -1;
};
