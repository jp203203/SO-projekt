#ifndef AIZO_PROJEKT2_GRAPHGENERATOR_H
#define AIZO_PROJEKT2_GRAPHGENERATOR_H


#include <tuple>
#include "GraphMatrix.h"
#include "GraphList.h"

class GraphGenerator {
public:
    std::tuple<GraphList, GraphMatrix> generateGraph(int no_of_vertexes, int density);
private:
    bool edgeExists(int u, int v, int created_edges[][3], int edge_count);
};


#endif //AIZO_PROJEKT2_GRAPHGENERATOR_H