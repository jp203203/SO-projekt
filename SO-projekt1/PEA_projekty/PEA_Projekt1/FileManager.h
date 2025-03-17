#ifndef PEA_PROJEKT1_FILEMANAGER_H
#define PEA_PROJEKT1_FILEMANAGER_H

#include <iostream>
#include <fstream>
#include "Graph.h"

class FileManager {
public:
    Graph loadGraph();
    void saveGraph(const Graph& graph);
};


#endif //PEA_PROJEKT1_FILEMANAGER_H
