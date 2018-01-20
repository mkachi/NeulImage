#include "Time.h"

using namespace std::chrono;

Time::Time()
    :_lastTime(high_resolution_clock::now())
    , _timeScale(1.0f)
    , _deltaTime(0.0f)
{	}

Time::~Time()
{	}

void Time::Tick()
{
    _curTime = high_resolution_clock::now();
    _deltaTime = duration_cast<nanoseconds>(_curTime - _lastTime).count();
    _deltaTime /= 1000000000;
    _lastTime = _curTime;
}

void Time::SetTimeScale(float scale)
{
    _timeScale = scale;
}