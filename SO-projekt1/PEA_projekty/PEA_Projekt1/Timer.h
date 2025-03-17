#ifndef PEA_PROJEKT1_TIMER_H
#define PEA_PROJEKT1_TIMER_H

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
    chrono::time_point<chrono::high_resolution_clock> startTime;
    chrono::time_point<chrono::high_resolution_clock> endTime;
};


#endif //PEA_PROJEKT1_TIMER_H
