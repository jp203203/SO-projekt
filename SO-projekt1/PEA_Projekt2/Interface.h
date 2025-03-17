#ifndef PEA_PROJEKT2_INTERFACE_H
#define PEA_PROJEKT2_INTERFACE_H


#include "FileManager.h"
#include "NearestNeighbor.h"
#include "TabuSearch.h"
#include "SimAnnealing.h"
#include "Graph.h"

class Interface {
public:
    Interface(FileManager fm, NearestNeighbor nn, SimAnnealing sa, TabuSearch ts);
    void menuScreen();
private:
    void loadFileScreen();
    void loadTourScreen();
    void addParametersScreen();
    void runAlgorithmScreen();
    void displayParameters();
    template <typename T> T optionInput(T limit, T lower_limit = 1);
    string extractNameFromPath(string file_path);
    void printTour(vector<int> tour, int** graph_matrix, int no_of_cities);

    FileManager file_manager;
    NearestNeighbor nearest_neighbor;
    SimAnnealing simulated_annealing;
    TabuSearch tabu_search;

    Graph graph;
    std::string atsp_file_name;
    int timeout_s;
    float cooling_factor;
};


#endif //PEA_PROJEKT2_INTERFACE_H
