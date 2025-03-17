#ifndef AIZO_PROJEKT2_INTERFACE_H
#define AIZO_PROJEKT2_INTERFACE_H
#include "GraphList.h"
#include "GraphMatrix.h"
#include "FileManager.h"
#include "MST.h"
#include "ShortestPath.h"
#include "GraphGenerator.h"
#include "Timer.h"


class Interface {
public:
    Interface(FileManager fm, MST mst, ShortestPath sp, GraphGenerator gg, Timer timer);
    void welcomeScreen();
private:
    void graphOptionsInterface(bool save_button, const GraphList& graph_list, const GraphMatrix& graph_matrix);
    void runOneOptions(const GraphList& graph_list, const GraphMatrix& graph_matrix);
    void runMultipleOptions();
    int optionInput(int limit, int lower_limit = 1);

    FileManager file_manager;
    MST mst_algorithms;
    ShortestPath sp_algorithms;
    GraphGenerator generator;
    Timer timer;
};


#endif //AIZO_PROJEKT2_INTERFACE_H
