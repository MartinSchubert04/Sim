#include "Planet.h"

Planet::Planet(Vector3 pos, float radius, float mass, Texture texture, Color color)
                      :  _pos(pos), _radius(radius), _mass(mass), _color(color) {

  _mesh = GenMeshSphere(_radius, 32, 32);
  _material = LoadMaterialDefault();
  _material.maps[MATERIAL_MAP_DIFFUSE].color = _color;
  _material.maps[MATERIAL_MAP_DIFFUSE].texture = texture;
}

void Planet::draw() {
  Matrix transform = MatrixTranslate(_pos.x, _pos.y, _pos.z);

  DrawMesh(_mesh, _material, transform);
}