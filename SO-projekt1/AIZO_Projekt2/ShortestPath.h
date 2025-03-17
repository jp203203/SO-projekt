#ifndef AIZO_PROJEKT2_SHORTESTPATH_H
#define AIZO_PROJEKT2_SHORTESTPATH_H
#include "GraphList.h"
#include "GraphMatrix.h"
#include "Queue.h"
#include "GEdge.h"

class ShortestPath {
public:
    int** DijkstraList(const GraphList& graph, int start);
    int** BellmanFordList(const GraphList& graph, int start);

    int** DijkstraMatrix(const GraphMatrix& graph, int start);
    int** BellmanFordMatrix(const GraphMatrix& graph, int start);

    void SPResult(int** dp, int start, int finish);
};


#endif //AIZO_PROJEKT2_SHORTESTPATH_H
