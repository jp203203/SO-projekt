#include "Graph.h"

//reprezentacja macierzowa grafu z funkcją wyświetlenia
Graph::Graph(int no_of_cities) {
    this->no_of_cities = no_of_cities; //przechowuje ilość miast

    graph_matrix = new int*[no_of_cities];
    for(int i = 0; i < no_of_cities; i++) {
        graph_matrix[i] = new int[no_of_cities];
        for(int j = 0; j < no_of_cities; j++) {
            graph_matrix[i][j] = (i == j) ? -1 : 0;
        }
    }
}

void Graph::displayGraphMatrix() {
    for(int i = 0; i < no_of_cities; i++) {
        for(int j = 0; j < no_of_cities; j++) {
            std::cout<<graph_matrix[i][j]<<" ";
        }
        std::cout<<"\n";
    }
}