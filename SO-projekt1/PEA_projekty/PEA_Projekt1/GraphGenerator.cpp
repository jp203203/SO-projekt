#include "GraphGenerator.h"

//generowanie grafu - losowe wartości (1,100) w komórkach
Graph GraphGenerator::generateGraph(int no_of_cities) {
    std::uniform_int_distribution<int> d_distribution(1, 100);

    Graph new_graph(no_of_cities);

    for(int i = 0; i < no_of_cities; i++) {
        for(int j = 0; j < no_of_cities; j++) {
            if(new_graph.cost_matrix[i][j] != -1) {
                new_graph.cost_matrix[i][j] = d_distribution(rand_generator);
            }
        }
    }

    return new_graph;
}
