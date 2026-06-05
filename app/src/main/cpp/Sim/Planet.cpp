#include "Planet.h"

Planet::Planet(std::string name, Vector3 pos, float radius, float mass, std::vector<Texture> textures, bool isStar)
                      :  _name(name), _pos(pos), _radius(radius), _mass(mass), _speed({0,0,0}), _isStar(isStar) {

  _shader = LoadShader("shaders/planet.vs", "shaders/planet.fs");

  Mesh mesh = GenMeshSphere(_radius, 32, 32);
  _model = LoadModelFromMesh(mesh);

  SetMaterialTexture(&_model.materials[0], MATERIAL_MAP_DIFFUSE, textures[0]);
  if (textures.size() > 1 && textures[1].id > 0)
      SetMaterialTexture(&_model.materials[0], MATERIAL_MAP_SPECULAR, textures[1]);
  if (textures.size() > 2 && textures[2].id > 0)
      SetMaterialTexture(&_model.materials[0], MATERIAL_MAP_NORMAL, textures[2]);

  _model.materials[0].shader = _shader;

  _lightPosLoc = GetShaderLocation(_shader, "lightPos");
  _camPosLoc   = GetShaderLocation(_shader, "camPos");
  _isStarLoc   = GetShaderLocation(_shader, "isStar");

  float isStarVal = _isStar ? 1.f : 0.f;
  SetShaderValue(_shader, _isStarLoc, &isStarVal, SHADER_UNIFORM_FLOAT);

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

void Planet::draw(Vector3 lightPos, Vector3 camPos) {
  SetShaderValue(_shader, _lightPosLoc, &lightPos, SHADER_UNIFORM_VEC3);
  SetShaderValue(_shader, _camPosLoc,   &camPos,   SHADER_UNIFORM_VEC3);
  DrawModel(_model, _pos, 1.f, WHITE);
}

void Planet::orbit(DeltaTime dt) {
  _orbitAngle += dt.getSeconds() * _orbitSpeed;

  _pos.x = _orbitRadius * cosf(_orbitAngle);
  _pos.z = _orbitRadius * sinf(_orbitAngle);
  // _pos.y queda fijo (órbita en plano horizontal)
}