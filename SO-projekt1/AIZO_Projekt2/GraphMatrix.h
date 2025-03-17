#ifndef AIZO_PROJEKT2_GRAPHMATRIX_H
#define AIZO_PROJEKT2_GRAPHMATRIX_H


class GraphMatrix {
public:
    GraphMatrix(int no_of_vertexes, int no_of_edges);

    void newEdge(int u, int v, int edge, int weight);
    void displayGraph() const;

    int no_of_vertexes;
    int no_of_edges;
    int** matrix;
    int* edge_weights;
};


#endif //AIZO_PROJEKT2_GRAPHMATRIX_H
