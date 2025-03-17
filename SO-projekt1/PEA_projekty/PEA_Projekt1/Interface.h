#ifndef PEA_PROJEKT1_INTERFACE_H
#define PEA_PROJEKT1_INTERFACE_H

#include "FileManager.h"
#include "Graph.h"
#include "GraphGenerator.h"
#include "BruteForce.h"
#include "BnBLittle.h"
#include "Dynamic.h"
#include "Timer.h"

class Interface {
public:
    Interface(FileManager fm, GraphGenerator gg, BruteForce bf, BnBLittle bnbl, Timer timer, Dynamic d);
    void welcomeScreen();
private:
    void graphOptionsInterface(bool save_button, const Graph& graph);
    void runOneOptions(const Graph& graph);
    void runMultipleOptions();
    int optionInput(int limit, int lower_limit = 1);

    FileManager file_manager;
    BruteForce brute_force;
    GraphGenerator generator;
    BnBLittle little;
    Dynamic dynamic;
    Timer timer;
};


#endif //PEA_PROJEKT1_INTERFACE_H
