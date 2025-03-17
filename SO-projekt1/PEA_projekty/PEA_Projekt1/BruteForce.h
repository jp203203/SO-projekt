#ifndef PEA_PROJEKT1_BRUTEFORCE_H
#define PEA_PROJEKT1_BRUTEFORCE_H

#include "Graph.h"

class BruteForce {
public:
    void findTourBF(const Graph& graph, bool print_result = true);
private:
    static void printTour(int* array, int tour_dist, int length);
    static int findBest(const Graph& graph, int* array);
    static int calculateTour(const Graph& graph, const int* array);
};


#endif //PEA_PROJEKT1_BRUTEFORCE_H
