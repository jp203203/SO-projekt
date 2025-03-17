#ifndef AIZO_PROJEKT2_TIMER_H
#define AIZO_PROJEKT2_TIMER_H

#include <iostream>
#include <chrono>

using namespace std;

class Timer {
public:
    Timer();

    void start();
    void stop();
    double getTime() const;

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> endTime;
};


#endif //AIZO_PROJEKT2_TIMER_H
