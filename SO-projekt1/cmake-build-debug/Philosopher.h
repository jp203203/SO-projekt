#ifndef SO2_PROJEKT1_PHILOSOPHER_H
#define SO2_PROJEKT1_PHILOSOPHER_H

#include <mutex>
#include <random>
#include <iostream>
#include <thread>

class Philosopher {
public:
    Philosopher(int id, std::mutex& left_fork, std::mutex& right_fork)
        : id(id), left_fork(left_fork), right_fork(right_fork) {};

    void startDining();

private:
    int id;
    //right and left forks implemented as mutexes
    std::mutex& left_fork;
    std::mutex& right_fork;
    //philosopher will randomly wait 10-20 seconds while thinking or eating
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<> dist{10, 20};

    void think();
    void eat();
};


#endif //SO2_PROJEKT1_PHILOSOPHER_H
