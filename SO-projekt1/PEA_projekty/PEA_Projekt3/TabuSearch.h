#ifndef PEA_PROJEKT2_TABUSEARCH_H
#define PEA_PROJEKT2_TABUSEARCH_H

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include <deque>
#include <map>
#include "Timer.h"

enum class NeighborhoodMethod {
    SWAP,
    REVERSE,
    INSERT
};

class TabuSearch {
public:
    TabuSearch();
    std::pair<std::vector<int>, int> findTabuSolution(int** graph_matrix, int no_of_cities, int timeout_s,
                                                      NeighborhoodMethod method, int tabu_limit, int diversify_point,
                                                      float time_interval);
private:
    std::vector<int> genInitTour(int no_of_cities, std::mt19937 gen);
    std::pair<std::vector<int>, std::pair<int, int>> neighborhoodSwap(const std::vector<int>& current_solution, int**graph_matrix, int no_of_cities, int best_distance);
    std::pair<std::vector<int>, std::pair<int, int>> neighborhoodReverse(const std::vector<int>& current_solution, int** graph_matrix, int no_of_cities, int best_distance);
    std::pair<std::vector<int>, std::pair<int, int>> neighborhoodInsert(const std::vector<int>& current_solution, int** graph_matrix, int no_of_cities, int best_distance);
    int calculateDistance(std::vector<int> tour, int** graph_matrix, int no_of_cities);
    void printSolution(std::vector<int> solution, int distance, int no_of_cities, double time);
    std::vector<int> reversePath(std::vector<int> tour, int first_city, int second_city, int no_of_cities);
    std::vector<int> insertCity(std::vector<int> tour, int insert_from, int insert_to, int no_of_cities);

    std::deque<std::pair<int, int>> tabu_list;
    Timer timer;
};


#endif //PEA_PROJEKT2_TABUSEARCH_H
