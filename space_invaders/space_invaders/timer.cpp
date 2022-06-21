#include "timer.h"

///Function which sets startTime at current moment
void Timer::reset() {
    startTime = std::chrono::system_clock::now();
}
///Non parameterized constructor, calls reset() function and sets deltaTime to zero
Timer::Timer() {
    reset();
    deltaTime = std::chrono::duration<float>(0.0f);
}
///Function returning value of deltaTime
float Timer::DeltaTime() {
    return deltaTime.count();
}
///Function calculating the value of deltaTime
void Timer::Tick() {
    deltaTime = std::chrono::system_clock::now() - startTime;
}