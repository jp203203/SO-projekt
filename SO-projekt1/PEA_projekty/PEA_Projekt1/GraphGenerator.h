#ifndef PEA_PROJEKT1_GRAPHGENERATOR_H
#define PEA_PROJEKT1_GRAPHGENERATOR_H

#include "Graph.h"
#include <ctime>
#include <random>
#include <cstdlib>

class GraphGenerator {
public:
    Graph generateGraph(int no_of_cities);
    GraphGenerator() : rand_generator(static_cast<unsigned int>(std::time(nullptr))) {}
private:
    std::mt19937 rand_generator;
};


#endif //PEA_PROJEKT1_GRAPHGENERATOR_H
