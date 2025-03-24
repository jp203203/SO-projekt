#include "Philosopher.h"

//global mutex for output synchronisation
std::mutex cout_mutex;

int Philosopher::num_philosophers = 0;

//philosopher thinks and eats in an endless loop
void Philosopher::startDining() {
    while(true) {
        eat();
        think();
    }
}

//simulates philosopher thinking
void Philosopher::think() {
    {
        std::lock_guard<std::mutex> lock(cout_mutex); //sync access to cout
        std::cout << "Philosopher " << id << " is thinking..." << std::endl;
    }

    //thread sleeps for random amount of time
    std::this_thread::sleep_for(std::chrono::seconds(dist(gen)));
}

//simulates philosopher eating
void Philosopher::eat() {
    {
        std::lock_guard<std::mutex> lock(cout_mutex); //sync access to cout
        std::cout << "Philosopher " << id << " wants to eat! Waiting for forks " << id << " and "
                  << (id + 1) % num_philosophers << "..." << std::endl;
    }
    //waits for both forks to be available, then locks them both at once to avoid deadlocks
    std::lock(left_fork, right_fork);

    //lock guards take ownership of the forks
    //when function goes out of scope, lock guards are terminated and forks are released
    std::lock_guard<std::mutex> left_lg(left_fork, std::adopt_lock);
    std::lock_guard<std::mutex> right_lg(right_fork, std::adopt_lock);

    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "Philosopher " << id << " is eating. Forks " << id << " and " << (id + 1) % num_philosophers
                  << " are taken..." << std::endl;
    }

    //thread sleeps for random amount of time
    std::this_thread::sleep_for(std::chrono::seconds(dist(gen)));

    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "Philosopher " << id << " stopped eating! Forks " << id << " and " << (id + 1) % num_philosophers
                  << " are released." << std::endl;
    }
}