#ifndef PEA_PROJEKT2_GRAPH_H
#define PEA_PROJEKT2_GRAPH_H

#include <iostream>

class Graph {
public:
    Graph(int no_of_cities);

    void displayGraphMatrix();

    int no_of_cities;
    int** graph_matrix;
};


#endif //PEA_PROJEKT2_GRAPH_H
