#pragma once

class Universe {

private:
    Universe() {}

public:

    static Universe *get() { return instance; }

private:
    static Universe *instance;
};



