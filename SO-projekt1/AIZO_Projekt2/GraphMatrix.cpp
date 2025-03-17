#include <iostream>
#include <iomanip>
#include "GraphMatrix.h"

GraphMatrix::GraphMatrix(int no_of_vertexes, int no_of_edges) {
    this -> no_of_vertexes = no_of_vertexes;
    this -> no_of_edges = no_of_edges;

    matrix = new int*[no_of_vertexes];
    edge_weights = new int[no_of_edges]; //dodatkowa tablica na wagi krawędzi

    for(int i = 0; i < no_of_vertexes; i++) { //wypełnia macierz zerami
        matrix[i] = new int[no_of_edges];
        for(int j = 0; j < no_of_edges; j++) {
            matrix[i][j] = 0;
        }
    }
    for(int i = 0; i < no_of_edges; i++) {
        edge_weights[i] = 0;
    }
}

//dodaje krawędź
void GraphMatrix::newEdge(int u, int v, int edge, int weight) {
    matrix[u][edge] = 1;
    matrix[v][edge] = -1;
    edge_weights[edge] = weight;
}

//wyświetla graf w postaci macierzy + wagi krawędzi
void GraphMatrix::displayGraph() const {
    std::cout<<"Postac macierzowa:\n";
    for(int i = 0; i < no_of_vertexes; i++) {
        for(int j = 0; j < no_of_edges; j++) {
            std::cout<<std::setfill(' ')<<std::setw(2)<<matrix[i][j]<<" ";
        }
        std::cout<<"\n";
    }
    std::cout<<"wagi krawedzi:\n";
    for(int i = 0; i < no_of_edges; i++) {
        std::cout<<std::setfill(' ')<<std::setw(2)<<edge_weights[i]<<" ";
    }
    std::cout<<"\n\n";
}

