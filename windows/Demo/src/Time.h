#pragma once

#include <chrono>

class Time
{
private:
    std::chrono::steady_clock::time_point _curTime;
    std::chrono::steady_clock::time_point _lastTime;
    float _deltaTime;
    float _timeScale;

public:
    Time();
    ~Time();

    void Tick();

    void SetTimeScale(float scale);
    float GetTimeScale() { return _timeScale; }
    float GetDeltaTime() { return _deltaTime * _timeScale; }

};