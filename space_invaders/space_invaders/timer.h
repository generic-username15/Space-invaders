#pragma once
#ifndef SPACE_INVADERS_TIMER_H
#define SPACE_INVADERS_TIMER_H
#include <chrono>

///Class designed to control time between certain events in the game
class Timer {
private:
    ///Variable storing time of creation of instance or time of latest Timer::reset()
    std::chrono::system_clock::time_point startTime;
    ///Variable storing time between startTimer and latest Timer::Tick() call
    std::chrono::duration<float> deltaTime;

public:

    void reset();

    float DeltaTime();

    void Tick();

    Timer();
};


#endif
