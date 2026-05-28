#pragma once

#include "DeltaTime.h"
#include "raymob.h"


class Application {

public:
    Application();

    void run();

    static Application *get() { return instance; }

private:
    static Application *instance;
    DeltaTime dt;
    Vector2 _window;
    float _lastTime;
};

Application *createApplication();
