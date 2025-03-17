#include "FileManager.h"

//wczytanie pliku .atsp
Graph FileManager::readATSPFile(const std::string& file_path) {
    std::ifstream file;
    file.open(file_path.c_str());

    std::string line;
    std::string keyword;
    int size = 0;

    while(std::getline(file, line)) {
        std::istringstream iss(line); //użycie istringstream do znajdowania "słów kluczy" w pliku
        iss >> keyword;

        if(keyword == "DIMENSION:") { //czytanie rozmiaru grafu
            iss >> size; //wczytanie rozmiaru problemu
        } else if(keyword == "EDGE_WEIGHT_SECTION") {
            break; //wyjście z pętli gdy napotka początek danych kosztów krawędzi
        }
    }
    Graph new_graph = Graph(size);

    //czytanie wartości krawędzi
    int value;
    int row = 0, col = 0;
    while(std::getline(file, line)) {
        std::istringstream iss(line);
        while(iss >> value) {
            new_graph.graph_matrix[row][col] = value;
            col++;
            if(col == size) {
                row++;
                col = 0;
            }
        }
        if(row == size) {
            break;
        }
    }

    file.close();
    return new_graph;
}

//generowanie pliku z trasą
void FileManager::generateTourFile(std::string atsp_file_name, int no_of_cities, std::vector<int> tour, int algorithm_choice, float cooling_factor) {
    std::string file_name = atsp_file_name;
    file_name.erase(file_name.end() - 4, file_name.end());
    std::string alg_prefix;
    switch(algorithm_choice) { //wybranie przedrostka na podstawie uzytego algorytmu
        case 1:
            alg_prefix = "ts_s_";
            break;
        case 2:
            alg_prefix = "ts_r_";
            break;
        case 3:
            alg_prefix = "ts_i_";
            break;
        case 4:
            alg_prefix = "sw_" + std::to_string(cooling_factor) + "_";
            break;
    }

    file_name = alg_prefix + file_name + "txt";

    std::ofstream file;
    file.open(file_name.c_str());

    file<<no_of_cities<<std::endl; //1. wiersz to liczba miast
    for(int i = 0; i <= no_of_cities; i++) { //pozostałe to miasta z zapętleniem (cykl kompletny)
        file<<tour[i % no_of_cities]<<std::endl;
    }

    file.close();
    std::cout<<"Zapisano sciezke\n";
}

//czytanie pliku z trasą
std::vector<int> FileManager::readTourFile(const std::string& file_path, int no_of_cities) {
    std::ifstream file;
    file.open(file_path.c_str());

    std::vector<int> tour;

    int no_of_cities_file;
    file>>no_of_cities_file;
    if(no_of_cities != no_of_cities_file) { //miasta muszą się zgadzać, jak nie to zwraca pusty zbiór
        std::cout<<"Niepoprawny plik!";
        return tour;
    }

    tour.resize(no_of_cities); //zmiana rozmiaru zbioru i czytanie miast
    for(int i = 0; i < no_of_cities; i++) {
        file>>tour[i];
    }

    file.close();
    return tour;
}