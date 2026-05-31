#pragma once

#include "pch.h"

class Global {

private:
  Global() {}

public:
  static inline Font font {0};


  void init() {
    font = LoadFontEx("font/anonymous_pro_bold.ttf", 128, 0, 0);
  }

  static Global& instance() {
    static Global inst; // ← esta línea es la clave
    return inst;
  }


private:
  static Global *_instance;



};

