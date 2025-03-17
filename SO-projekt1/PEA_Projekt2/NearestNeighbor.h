#ifndef PEA_PROJEKT2_NEARESTNEIGHBOR_H
#define PEA_PROJEKT2_NEARESTNEIGHBOR_H

#include <vector>
#include "Graph.h"

class NearestNeighbor {
public:
    void findNNSolution(const Graph& graph);
    int calculateDistance(const std::vector<int>& tour, int** graph_matrix, int no_of_cities);
private:
    std::vector<int> findNNPartial(int start, int** graph_matrix, int no_of_cities);
    void printSolution(const std::vector<int>& solution, int distance, int no_of_cities);
};


#endif //PEA_PROJEKT2_NEARESTNEIGHBOR_H
