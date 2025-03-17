#include <algorithm>
#include <iostream>
#include "MST.h"

int** MST::PrimList(const GraphList& graph, int start) {
    int** kp = new int*[2]; //tablica dwuwymiarowa z informacją o koszcie i rodzicu
    kp[0] = new int[graph.no_of_vertexes];
    kp[1] = new int[graph.no_of_vertexes];

    for(int v = 0; v < graph.no_of_vertexes; v++) {
        kp[0][v] = 1000000;
    }

    kp[0][start] = 0;
    kp[1][start] = -1;

    Queue q = Queue(kp[0], graph.no_of_vertexes);
    while(!q.is_empty()) {
        int u = q.extract_min();
        GraphList::Node* node = graph.list[u].first_node;

        while(node != nullptr) {
            int v = node -> dest_vertex;
            if(q.contains_index(v) && node -> weight < kp[0][v]) { //zmniejszanie kosztu
                kp[0][v] = node -> weight;
                kp[1][v] = u;
                q.fix_queue(v); //aktualizacja kolejki
            }
            node = node -> next;
        }
    }

    return kp; //zwraca tablicę
}

int** MST::PrimMatrix(const GraphMatrix& graph, int start) {
    int** kp = new int*[2];
    kp[0] = new int[graph.no_of_vertexes];
    kp[1] = new int[graph.no_of_vertexes];

    for(int v = 0; v < graph.no_of_vertexes; v++) {
        kp[0][v] = 1000000;
    }

    kp[0][start] = 0;
    kp[1][start] = -1;

    Queue q = Queue(kp[0], graph.no_of_vertexes);
    while(!q.is_empty()) {
        int u = q.extract_min();
        int edge_index = graph.no_of_edges; //szuka pierwszej krawędzi wychodzącej z wierzchołka
        for(int i = 0; i < graph.no_of_edges; i++) {
            if(graph.matrix[u][i] != 0) { //warunek !=0 bo graf nieskierowany
                edge_index = i;
                break;
            }
        }

        while(edge_index < graph.no_of_edges){
            int v = u;
            for(int i = 0; i < graph.no_of_vertexes; i++) { //szuka wierzchołka końcowego dla krawędzi
                if(i != u && graph.matrix[i][edge_index] != 0) {
                    v = i;
                    break;
                }
            }
            if(q.contains_index(v) && graph.edge_weights[edge_index] < kp[0][v]) { //zmniejszanie kosztu
                kp[0][v] = graph.edge_weights[edge_index];
                kp[1][v] = u;
                q.fix_queue(v);
            }

            edge_index++;
            if(edge_index == graph.no_of_edges) { //przerywa, gdy ostatnia krawędź
                break;
            }
            for(int i = edge_index; i < graph.no_of_edges; i++) { //szuka kolejnej krawędzi dla wierzchołka u
                if(graph.matrix[u][i] != 0) {
                    edge_index = i;
                    break;
                }
                edge_index = graph.no_of_edges;
            }
        }
    }

    return kp; //zwraca tablicę
}

//na podstawie tablicy zwraca informację o MST
void MST::PrimResult(int** kp, int no_of_vertexes) {
    int MST_weight = 0;
    std::cout<<"Drzewo MST:\n";
    for(int i = 0; i < no_of_vertexes; i++) {
        MST_weight += kp[0][i];
        std::cout<<"Wierzcholek "<<i<<": "
                 <<"poprzednik = "<<kp[1][i]<<", waga = "<<kp[0][i]<<"\n";
    }
    std::cout<<"Waga drzewa MST = "<<MST_weight<<"\n";
}

GEdge::Edge* MST::KruskalList(const GraphList& graph) {
    auto* mst_edges = new GEdge::Edge[graph.no_of_vertexes - 1]; //tworzy tablicę na krawędzie MST (na razie pusta)
    Sets sets(graph.no_of_vertexes);

    GEdge::Edge* edges = GEdge::getEdgesList(graph); //pobiera tablicę krawędzi
    GEdge::sortEdges(edges, 0, graph.no_of_edges - 1);

    int current_edge = 0;
    for(int i = 0; i < graph.no_of_edges; i++){
        GEdge::Edge edge = edges[i];
        if(sets.findSet(edge.u) != sets.findSet(edge.v)) { //szukanie podzbiorów i ewentualne łączenie
            mst_edges[current_edge] = edge;
            current_edge++;
            sets.mergeSets(edge.u, edge.v);
        }
    }

    return mst_edges; //zwraca tablicę krawędzi MST
}

GEdge::Edge* MST::KruskalMatrix(const GraphMatrix& graph) {
    auto* mst_edges = new GEdge::Edge[graph.no_of_vertexes - 1];
    Sets sets(graph.no_of_vertexes);

    GEdge::Edge* edges = GEdge::getEdgesMatrix(graph);
    GEdge::sortEdges(edges, 0, graph.no_of_edges - 1);

    int current_edge = 0;
    for(int i = 0; i < graph.no_of_edges; i++){
        GEdge::Edge edge = edges[i];
        if(sets.findSet(edge.u) != sets.findSet(edge.v)) {
            mst_edges[current_edge] = edge;
            current_edge++;
            sets.mergeSets(edge.u, edge.v);
        }
    }

    return mst_edges;
}

//wyświetla wyniki na podstawie tablicy krawędzi
void MST::KruskalResult(GEdge::Edge *edges, int no_of_edges) {
    int MST_weight = 0;
    std::cout<<"Drzewo MST:\n";
    for(int i = 0; i < no_of_edges; i++) {
        MST_weight += edges[i].weight;
        std::cout<<"Krawedz "<<i<<" ("<<edges[i].u<<" - "<<edges[i].v<<"): waga = "<<edges[i].weight<<"\n";
    }
    std::cout<<"Waga drzewa MST = "<<MST_weight<<"\n";
}