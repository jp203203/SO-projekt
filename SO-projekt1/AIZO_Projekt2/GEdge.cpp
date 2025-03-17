#include <algorithm>
#include "GEdge.h"

//sortuje krawędzie quicksortem
void GEdge::sortEdges(GEdge::Edge *edges, int l, int r) {
    if(l >= r) return;
    int m = partition(edges, l, r);

    sortEdges(edges, l, m);
    sortEdges(edges, m+1, r);
}

int GEdge::partition(GEdge::Edge* edges, int l, int r) {
    int pivot = edges[(int)(l + r) / 2].weight; //środkowy pivot

    int left = l;
    int right = r;

    while(true) {
        while(edges[left].weight < pivot) left++;
        while(edges[right].weight > pivot) right--;

        if(left < right) {
            std::swap(edges[left], edges[right]);
            left++;
            right--;
        }else {
            if(r == right) right--;
            return right;
        }
    }
}

//zwraca tablice krawędzi dla grafu w postaci listy
GEdge::Edge* GEdge::getEdgesList(const GraphList& graph) {
    Edge* edges = new Edge[graph.no_of_edges];
    int current_edge = 0;
    for(int i = 0; i < graph.no_of_vertexes; i++) {
        GraphList::Node* node = graph.list[i].first_node; //czyta każdy węzeł, tworzy krawędź na jego podstawie
        while(node != nullptr) {
            if(node -> is_directed) {
                edges[current_edge] = {i, node->dest_vertex, node->weight};
                current_edge++;
            }
            node = node -> next;
        }
    }
    return edges;
}

//zwraca tablice krawędzi dla grafu w postaci macierzy
GEdge::Edge* GEdge::getEdgesMatrix(const GraphMatrix& graph) {
    Edge* edges = new Edge[graph.no_of_edges];
    for(int i = 0; i < graph.no_of_edges; i++) { //iteruje po krawędziach
        int u, v;
        for(int j = 0; j < graph.no_of_vertexes; j++) {
            if(graph.matrix[j][i] > 0) { //szuka u
                u = j;
                break;
            }
        }
        for(int j = 0; j < graph.no_of_vertexes; j++) {
            if(graph.matrix[j][i] < 0) { //szuka v
                v = j;
                break;
            }
        }
        edges[i] = {u, v, graph.edge_weights[i]};
    }
    return edges;
}