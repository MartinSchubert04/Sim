#pragma once

#include "pch.h"
#include "Planet.h"

class Universe {

public:
  static float G;

  Universe() = default;
  void update(DeltaTime dt);
  void draw();

  void add(Planet &p) { entities.push_back(p); }

  Planet &getEntity(std::string name) {
    for (auto &e : entities) {
      if (e._name == name) return e;
    }
    throw std::runtime_error("Planet not found");
  }
  static Planet &getStar() { return sun; }
  static std::vector<Planet> &getEntities() { return entities; }

  void setStar(Planet &s) { sun = s; }

private:
  void updateOrbits(DeltaTime dt);


private:
  static std::vector<Planet> entities;
  static Planet sun;
};



