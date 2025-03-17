#ifndef AIZO_PROJEKT2_FILEMANAGER_H
#define AIZO_PROJEKT2_FILEMANAGER_H

#include <iostream>
#include "GraphList.h"
#include "GraphMatrix.h"

class FileManager {
public:
    std::tuple<GraphList, GraphMatrix> loadGraph();
    void saveGraph(const GraphMatrix& graph);
};


#endif //AIZO_PROJEKT2_FILEMANAGER_H
