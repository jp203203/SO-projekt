#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include "Philosopher.h"

int main(int argc, char* argv[]) {
    //check for number of passed arguments
    if(argc != 2) {
        std::cerr << "Incorrect number of arguments!" << std::endl;
        return 1;
    }

    int num_philosophers = std::stoi(argv[1]);
    //check for correct argument value
    if(num_philosophers < 2) {
        std::cerr << "Incorrect argument value! (no. of philosophers must be greater than 1)" << std::endl;
        return 1;
    }

    Philosopher::num_philosophers = num_philosophers; //pass number of philosophers to the class

    std::vector<std::mutex> forks(num_philosophers); //vector of forks
    std::vector<std::thread> phil_threads; //vector of philosopher threads
    //ownership of object is required, so unique_ptr is used
    std::vector<std::unique_ptr<Philosopher>> philosophers;

    //creation of philosophers and assignment of forks
    for(int i = 0; i < num_philosophers; i++) {
        philosophers.push_back(std::make_unique<Philosopher>(i, forks[i], forks[(i + 1) % num_philosophers]));
    }

    //start thread for each philosopher
    for(int i = 0; i < num_philosophers; i++) {
        phil_threads.emplace_back(&Philosopher::startDining, philosophers[i].get());
    }

    //wait for threads to end
    for(auto& thread : phil_threads) {
        thread.join();
    }

    return 0;
}
