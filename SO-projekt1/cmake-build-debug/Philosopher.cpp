#include "Philosopher.h"

//philosopher thinks and eats in an endless loop
void Philosopher::startDining() {
    while(true) {
        think();
        eat();
    }
}

//simulates philosopher thinking
void Philosopher::think() {
    std::cout << "Philosopher " << id << "is thinking...\n";

    //thread sleeps for random amount of time
    std::this_thread::sleep_for(std::chrono::seconds(dist(gen)));
}

//simulates philosopher eating
void Philosopher::eat() {
    //waits for both forks to be available, then locks them both at once to avoid deadlocks
    std::lock(left_fork, right_fork);

    //lock guards take ownership of the forks
    //when function goes out of scope, lock guards are terminated and forks are released
    std::lock_guard<std::mutex> left_lg(left_fork, std::adopt_lock);
    std::lock_guard<std::mutex> right_lg(right_fork, std::adopt_lock);

    //thread sleeps for random amount of time
    std::cout << "Philosopher " << id << "is eating...\n";
    std::this_thread::sleep_for(std::chrono::seconds(dist(gen)));
    std::cout << "Philosopher " << id << "stopped eating! Forks are released\n";
}