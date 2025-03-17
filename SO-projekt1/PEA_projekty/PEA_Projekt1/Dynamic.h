#ifndef PEA_PROJEKT1_DYNAMIC_H
#define PEA_PROJEKT1_DYNAMIC_H

#include "Graph.h"

class Dynamic {
public:
    void findTourDynamic(const Graph& graph, bool print_result = true);
private:
    static int** copyCostMatrix(int** cost_matrix, int side_length);
    static int findShortestDist(int position, int visited_mask, int** dist_matrix, int** sub_dists, int** parents, int no_of_cities);
    static void printTour(int** parents, int shortest_dist, int no_of_cities);
};


#endif //PEA_PROJEKT1_DYNAMIC_H
