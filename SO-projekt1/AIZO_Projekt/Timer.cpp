
#include <chrono>
#include "Timer.h"

Timer::Timer(){}

//rozpoczęcie odmierzania czasu
void Timer::start(){
    startTime = std::chrono::high_resolution_clock::now();
}

//zakończenie odmierzania czasu
void Timer::stop(){
    endTime = std::chrono::high_resolution_clock::now();
}

//zwrócenie pomiaru czasu
double Timer::getTime() const{
    return std::chrono::duration<double, std::milli>(endTime - startTime).count();
}
