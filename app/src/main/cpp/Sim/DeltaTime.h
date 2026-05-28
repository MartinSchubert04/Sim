#pragma once

class DeltaTime {
public:
    DeltaTime(float time = 0.0f) : mTime(time) {};

    float getSeconds() const { return mTime; }
    float getMilliseconds() const { return mTime * 1000; }

private:
    float mTime;
};