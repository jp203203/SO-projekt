#ifndef AIZO_PROJEKT2_GRAPHLIST_H
#define AIZO_PROJEKT2_GRAPHLIST_H


class GraphList {
public:
    struct Node {                   // węzeł - opisuje krawędź
        int dest_vertex;            // wierzchołek, do którego wchodzi krawędź
        int weight;
        bool is_directed;
        Node* next;                 // wskaźnik na następny węzeł
    };

private:
    struct AdjList {                // lista sąsiadów pojedynczego wierzchołka
        Node* first_node;
    };

    Node* createNode(int vertex, int weight);


public:
    GraphList(int no_of_vertexes, int no_of_edges);

    void newEdge(int u, int v, int weight);
    void displayGraph() const;

    int no_of_vertexes;
    int no_of_edges;
    AdjList* list;
};



#endif //AIZO_PROJEKT2_GRAPHLIST_H
