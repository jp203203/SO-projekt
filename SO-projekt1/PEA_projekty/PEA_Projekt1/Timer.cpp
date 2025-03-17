#include "Timer.h"

Timer::Timer() {}

void Timer::start() {
    startTime = chrono::high_resolution_clock::now();
}

void Timer::stop() {
    endTime = chrono::high_resolution_clock::now();
}

double Timer::getTime() const {
    return chrono::duration<double, milli>(endTime - startTime).count();
}
