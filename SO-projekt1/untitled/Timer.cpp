#include <iostream>
#include <chrono>
#include "Timer.h"

Timer::Timer(){}

void Timer::start(){
    startTime = std::chrono::high_resolution_clock::now();
}

void Timer::stop(){
    endTime = std::chrono::high_resolution_clock::now();
}

double Timer::getTime() const{
    return std::chrono::duration<double, std::milli>(endTime - startTime).count();
}
