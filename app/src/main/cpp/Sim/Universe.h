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
  void setStar(Planet &s) { sun = s; }

private:
  void updateOrbits(DeltaTime dt);


private:
  std::vector<Planet> entities;
  Planet sun;

};



