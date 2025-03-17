#ifndef PEA_PROJEKT2_FILEMANAGER_H
#define PEA_PROJEKT2_FILEMANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>
#include "Graph.h"

class FileManager {
public:
    Graph readATSPFile(const std::string& file_path);
    void generateTourFile(std::string atsp_file_name, int no_of_cities, std::vector<int> tour, int algorithm_choice, float cooling_factor);
    std::vector<int> readTourFile(const std::string& file_path, int no_of_cities);
    void saveCSVFile_GA(const std::vector<float>& cost_evolution, int crossover, int mutation, float mr, float xr, int pop, int ti);
    void saveCSVFile_TS(const std::vector<int>& cost_evolution, int problem_size, int neighborhood, int ti);
    void saveCSVFile_SA(const std::vector<int>& cost_evolution, int problem_size, float cooling_rate, int ti);
};


#endif //PEA_PROJEKT2_FILEMANAGER_H
