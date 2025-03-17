#ifndef UNTITLED_TIMER_H
#define UNTITLED_TIMER_H

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


#endif //UNTITLED_TIMER_H
