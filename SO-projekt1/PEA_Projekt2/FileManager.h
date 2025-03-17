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
};


#endif //PEA_PROJEKT2_FILEMANAGER_H
