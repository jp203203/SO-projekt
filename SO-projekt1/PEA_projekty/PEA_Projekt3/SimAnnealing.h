#ifndef PEA_PROJEKT2_SIMANNEALING_H
#define PEA_PROJEKT2_SIMANNEALING_H


#include <vector>
#include <random>
#include "Timer.h"
#include <algorithm>
#include <iomanip>

class SimAnnealing {
public:
    SimAnnealing();
    std::pair<std::vector<int>, int> findAnnealingSolution(int** graph_matrix, int no_of_cities, int timeout_s,
                                                           float cooling_factor, float time_interval);
private:
    std::vector<int> genInitTour(int no_of_cities, std::mt19937 gen);
    std::vector<int> reversePath(std::vector<int> tour, int no_of_cities, std::mt19937 gen);
    std::vector<int> insertPath(std::vector<int> tour, int no_of_cities, std::mt19937 gen);
    int calculateDistance(std::vector<int> solution, int no_of_cities, int** graph_matrix);
    void printSolution(std::vector<int> solution, int distance, int no_of_cities, double time, double end_temp);

    Timer timer;
};


#endif //PEA_PROJEKT2_SIMANNEALING_H
