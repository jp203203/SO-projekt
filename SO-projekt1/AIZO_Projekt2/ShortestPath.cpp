#include <iostream>
#include "ShortestPath.h"

int** ShortestPath::DijkstraList(const GraphList& graph, int start) {
    int** dp = new int*[2]; //tablica dwuwymiarowa przechowująca odległość i rodzica
    dp[0] = new int[graph.no_of_vertexes];
    dp[1] = new int[graph.no_of_vertexes];

    for(int v = 0; v < graph.no_of_vertexes; v++) {
        dp[0][v] = 1000000;
        dp[1][v] = -1;
    }

    dp[0][start] = 0;

    Queue q(dp[0], graph.no_of_vertexes); //ładuje tablicę z odl. do kolejki priorytetowej
    while(!q.is_empty()) {
        int u = q.extract_min();

        GraphList::Node* node = graph.list[u].first_node;
        while(node != nullptr) {
            if(node -> is_directed) { //działa tylko na krawędziach grafu skierowanego
                int v = node -> dest_vertex;
                if (dp[0][v] > dp[0][u] + node -> weight) { //relaksacja
                    dp[0][v] = dp[0][u] + node -> weight;
                    dp[1][v] = u;
                    q.fix_queue(v);
                }
            }
            node = node -> next;
        }
    }
    return dp; //zwraca tablicę z odległościami i rodzicami
}

int** ShortestPath::DijkstraMatrix(const GraphMatrix& graph, int start) {
    int** dp = new int*[2];
    dp[0] = new int[graph.no_of_vertexes];
    dp[1] = new int[graph.no_of_vertexes];

    for(int v = 0; v < graph.no_of_vertexes; v++) {
        dp[0][v] = 1000000;
        dp[1][v] = -1;
    }

    dp[0][start] = 0;

    Queue q(dp[0], graph.no_of_vertexes);
    while(!q.is_empty()) {
        int u = q.extract_min();

        int edge_index = graph.no_of_edges; //znajduje pierwszą krawędź
        for(int i = 0; i < graph.no_of_edges; i++) {
            if(graph.matrix[u][i] > 0) {
                edge_index = i;
                break;
            }
        }

        while(edge_index < graph.no_of_edges) {
            int v = u;
            for(int i = 0; i < graph.no_of_vertexes; i++) { //znajduje sąsiada dla krawędzi
                if(i != u && graph.matrix[i][edge_index] < 0) {
                    v = i;
                    break;
                }
            }

            if(dp[0][v] > dp[0][u] + graph.edge_weights[edge_index]) { //relaksacja
                dp[0][v] = dp[0][u] + graph.edge_weights[edge_index];
                dp[1][v] = u;
                q.fix_queue(v);
            }

            edge_index++;
            if(edge_index == graph.no_of_edges) { //przerywa, gdy badana jest ostatnia krawędź
                break;
            }
            for(int i = edge_index; i < graph.no_of_edges; i++) { //szuka kolejnych krawędzi dla wierzchołka u
                if(graph.matrix[u][i] > 0) {
                    edge_index = i;
                    break;
                }
                edge_index = graph.no_of_edges;
            }
        }
    }

    return dp;
}

int** ShortestPath::BellmanFordList(const GraphList& graph, int start) {
    int** dp = new int*[2];
    dp[0] = new int[graph.no_of_vertexes];
    dp[1] = new int[graph.no_of_vertexes];

    for(int v = 0; v < graph.no_of_vertexes; v++) {
        dp[0][v] = 1000000;
        dp[1][v] = -1;
    }
    dp[0][start] = 0;

    GEdge::Edge* edges = GEdge::getEdgesList(graph); //pobiera tablicę krawędzi

    for(int i = 1; i < graph.no_of_vertexes; i++) { //pętla v-1 razy
        for(int j = 0; j < graph.no_of_edges; j++) { //iteracja po krawędziach
            if(dp[0][edges[j].v] > dp[0][edges[j].u] + edges[j].weight) { //relaksacja
                dp[0][edges[j].v] = dp[0][edges[j].u] + edges[j].weight;
                dp[1][edges[j].v] = edges[j].u;
            }
        }
    }

    return dp;
}

int** ShortestPath::BellmanFordMatrix(const GraphMatrix& graph, int start) {
    int** dp = new int*[2];
    dp[0] = new int[graph.no_of_vertexes];
    dp[1] = new int[graph.no_of_vertexes];

    for(int v = 0; v < graph.no_of_vertexes; v++) {
        dp[0][v] = 1000000;
        dp[1][v] = -1;
    }
    dp[0][start] = 0;

    GEdge::Edge* edges = GEdge::getEdgesMatrix(graph);

    for(int i = 1; i < graph.no_of_vertexes; i++) {
        for(int j = 0; j < graph.no_of_edges; j++) {
            if(dp[0][edges[j].v] > dp[0][edges[j].u] + edges[j].weight) {
                dp[0][edges[j].v] = dp[0][edges[j].u] + edges[j].weight;
                dp[1][edges[j].v] = edges[j].u;
            }
        }
    }

    for(int i = 0; i < graph.no_of_edges; i++) {
        if(dp[0][edges[i].v] > dp[0][edges[i].u] + edges[i].weight) {
            return nullptr;
        }
    }

    return dp;
}

//wyświetla optymalną ścieżkę od wierzchołka start do finish na podstawie zwróconej tablicy
void ShortestPath::SPResult(int **dp, int start, int finish) {
    if (dp[1][finish] == -1) { //brak ścieżki
        std::cout << "Brak sciezki od " << start << " do " << finish << "!\n";
        return;
    }
    std::cout << "Od konca do poczatku:\n";
    int v = finish;
    while (v != start) {
        std::cout << v << " <- ";
        v = dp[1][v];
    }
    std::cout << start << "\ndystans = " << dp[0][finish] << "\n";
}