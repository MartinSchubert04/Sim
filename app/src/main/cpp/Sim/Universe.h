#pragma once

#include "pch.h"
#include "Planet.h"

class Universe {

public:
  static float G;

  Universe() = default;
  void update(DeltaTime dt);
  void draw(Vector3 camPos);

  void add(const PlanetSpec &spec) {
    auto p = createRef<Planet>(spec.name, spec.pos, spec.radius, spec.mass,
                               std::vector<Texture>{spec.colorMap, spec.specularMap, spec.nightMap},
                               spec.isStar);
    if (sun) {
      float r = Vector3Distance(sun->_pos, p->_pos);
      float v = sqrtf(G * sun->_mass / r);
      p->_speed = {v, 0, 0};
    }
    entities.push_back(p);
  }

  void setStar(const PlanetSpec &spec) {
    sun = createRef<Planet>(spec.name, spec.pos, spec.radius, spec.mass,
                            std::vector<Texture>{spec.colorMap}, spec.isStar);
  }

  Ref<Planet> getEntity(const std::string &name) {
    for (auto &e : entities) {
      if (e->_name == name) return e;
    }
    throw std::runtime_error("Planet not found");
  }
  static Ref<Planet> getStar() { return sun; }
  static std::vector<Ref<Planet>> &getEntities() { return entities; }


private:
  void updateOrbits(DeltaTime dt);

private:
  static std::vector<Ref<Planet>> entities;
  static Ref<Planet> sun;
};



