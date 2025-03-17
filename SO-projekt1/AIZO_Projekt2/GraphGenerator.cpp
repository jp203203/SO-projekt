#include <cstdlib>
#include <ctime>
#include <random>
#include "GraphGenerator.h"

std::tuple<GraphList, GraphMatrix> GraphGenerator::generateGraph(int no_of_vertexes, int density) {
    //oblicza ilość krawędzi
    int max_edges = no_of_vertexes * (no_of_vertexes - 1) / 2;
    int no_of_edges = max_edges * (density / 100.0);

    std::mt19937 rand_generator(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<int> v_distribution(0, no_of_vertexes - 1); //przedział dla wierzchołków
    std::uniform_int_distribution<int> w_distribution(1, 70); //przedział dla wag krawędzi
    int created_edges[no_of_edges][3]; //tablica istniejących krawędzi
    int edge_count = 0;

    GraphMatrix graph_m(no_of_vertexes, no_of_edges);
    GraphList graph_l(no_of_vertexes, no_of_edges);

    for(int i = 0; i < no_of_vertexes - 1; i++) { //tworzy spójny graf
        int weight = w_distribution(rand_generator);
        created_edges[edge_count][0] = i;
        created_edges[edge_count][1] = i + 1;
        created_edges[edge_count][2] = weight;
        graph_m.newEdge(i, i + 1, edge_count, weight);
        graph_l.newEdge(i, i + 1, weight);
        edge_count++;
    }

    while(edge_count < no_of_edges) {
        int u = v_distribution(rand_generator); //losuje u i v
        int v = v_distribution(rand_generator);
        while(u == v || edgeExists(u, v, created_edges, edge_count)) { //sprawdza, czy u i v są równe lub czy krawędź istnieje
            u = std::rand() % no_of_vertexes;
            v = std::rand() % no_of_vertexes;
        }
        int weight = w_distribution(rand_generator);

        created_edges[edge_count][0] = u; //dodaje nową krawędź
        created_edges[edge_count][1] = v;
        created_edges[edge_count][2] = weight;
        graph_m.newEdge(u, v, edge_count, weight);
        graph_l.newEdge(u, v, weight);
        edge_count++;
    }

    return {std::move(graph_l), std::move(graph_m)}; //zwraca graf w obu reprezentacjach
}

//sprawdza, czy krawędź istnieje
bool GraphGenerator::edgeExists(int u, int v, int created_edges[][3], int edge_count) {
    for (int i = 0; i < edge_count; i++) {
        if (created_edges[i][0] == u && created_edges[i][1] == v || (created_edges[i][0] == v && created_edges[i][1] == u)) {
            return true;
        }
    }

    return false;
}