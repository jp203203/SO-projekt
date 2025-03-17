#ifndef AIZO_PROJEKT2_MST_H
#define AIZO_PROJEKT2_MST_H
#include "GraphList.h"
#include "GraphMatrix.h"
#include "Queue.h"
#include "Sets.h"
#include "GEdge.h"


class MST {
public:

    int** PrimList(const GraphList& graph, int start);
    GEdge::Edge* KruskalList(const GraphList& graph);

    int** PrimMatrix(const GraphMatrix& graph, int start);
    GEdge::Edge* KruskalMatrix(const GraphMatrix& graph);

    void PrimResult(int** kp, int no_of_vertexes);
    void KruskalResult(GEdge::Edge* edges, int no_of_edges);
};


#endif //AIZO_PROJEKT2_MST_H
