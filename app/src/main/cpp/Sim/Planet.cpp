#include "Planet.h"

Planet::Planet(std::string name, Vector3 pos, float radius, float mass, Texture texture, Color color)
                      :  _name(name), _pos(pos), _radius(radius), _mass(mass), _color(color), _speed({0,0,0}) {

  Mesh mesh = GenMeshSphere(_radius, 32, 32);
  _model = LoadModelFromMesh(mesh);
  _material = LoadMaterialDefault();
  _material.maps[MATERIAL_MAP_DIFFUSE].color = _color;
  _material.maps[MATERIAL_MAP_DIFFUSE].texture = texture;
  SetMaterialTexture(&_model.materials[0], MATERIAL_MAP_DIFFUSE, texture);

  Matrix correction = MatrixRotateX(DEG2RAD * -90.0f);
  _model.transform = correction;
}

Planet::~Planet() {
  UnloadModel(_model);
}

void Planet::update(DeltaTime dt) {
  _rotationAngle += dt.getSeconds() * 20.0f;

  float tilt = 23.44;

  Matrix correction = MatrixRotateX(DEG2RAD * (-90.0f + tilt));
  Matrix rotation   = MatrixRotateY(DEG2RAD * _rotationAngle);

  _model.transform = MatrixMultiply(correction, rotation);

  _pos = Vector3Add(_pos, Vector3Scale(_speed, dt.getSeconds()));

//  orbit(dt);
}

void Planet::draw() {
  DrawModel(_model, _pos, 1.f, _color);
}

void Planet::orbit(DeltaTime dt) {
  _orbitAngle += dt.getSeconds() * _orbitSpeed;

  _pos.x = _orbitRadius * cosf(_orbitAngle);
  _pos.z = _orbitRadius * sinf(_orbitAngle);
  // _pos.y queda fijo (órbita en plano horizontal)
}