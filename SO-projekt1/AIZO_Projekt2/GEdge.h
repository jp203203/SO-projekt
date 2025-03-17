#ifndef AIZO_PROJEKT2_GEDGE_H
#define AIZO_PROJEKT2_GEDGE_H
#include "GraphMatrix.h"
#include "GraphList.h"


class GEdge {
public:
    struct Edge{
        int u, v, weight;
    };

    static void sortEdges(Edge* edges, int l, int r);
    static Edge* getEdgesMatrix(const GraphMatrix& graph);
    static Edge* getEdgesList(const GraphList& graph);

private:
    static int partition(Edge* edges, int l, int r);
};


#endif //AIZO_PROJEKT2_GEDGE_H
