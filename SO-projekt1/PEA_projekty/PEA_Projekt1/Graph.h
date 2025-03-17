#ifndef PEA_PROJEKT1_GRAPH_H
#define PEA_PROJEKT1_GRAPH_H

#include <iostream>

class Graph {
public:
    Graph(int no_of_cities);

    void displayGraph() const;
    void addDistance(int start, int dest, int distance) const;

    int no_of_cities;
    int** cost_matrix;
};


#endif //PEA_PROJEKT1_GRAPH_H
