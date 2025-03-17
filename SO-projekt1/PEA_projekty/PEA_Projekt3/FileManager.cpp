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

void FileManager::saveCSVFile_GA(const std::vector<float>& cost_evolution, int crossover, int mutation, float mr,
                                 float xr, int pop, int ti) {
    std::string x_prefix;
    std::string m_prefix;

    if(crossover == 1) {
        x_prefix = "ga_ox_";
    } else if(crossover == 2) {
        x_prefix = "ga_scx_";
    }

    if(mutation == 1) {
        m_prefix = "_swap_";
    } else if(mutation == 2) {
        m_prefix = "_insert_";
    }

    std::string file_path = "C:\\Users\\kubap\\Desktop\\PEA2\\GA WYNIKI\\" + x_prefix + std::to_string(xr) + m_prefix
                            + std::to_string(mr) + "_p" + std::to_string(pop) + ".csv";

    std::ofstream file(file_path);
    if(!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku!";
        return;
    }

    int i = 0;

    file << "czas [s];śr. koszt\n";

    for(float cost : cost_evolution) {
        file << ti * i << ";" << cost << "\n";
        i++;
    }

    file.close();
}

void FileManager::saveCSVFile_TS(const std::vector<int>& cost_evolution, int problem_size, int neighborhood, int ti) {
    std::string n_prefix;

    if(neighborhood == 1) {
        n_prefix = "ts_swap_";
    } else if(neighborhood == 2) {
        n_prefix = "ts_reverse_";
    } else if(neighborhood == 3) {
        n_prefix = "ts_insert_";
    }

    std::string file_path = "C:\\Users\\kubap\\Desktop\\PEA2\\GA WYNIKI\\" + n_prefix + std::to_string(problem_size)
                            + ".csv";

    std::ofstream file(file_path);
    if(!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku!";
        return;
    }

    int i = 0;

    file << "czas [s];koszt\n";

    for(float cost : cost_evolution) {
        file << ti * i << ";" << cost << "\n";
        i++;
    }

    file.close();
}

void FileManager::saveCSVFile_SA(const std::vector<int>& cost_evolution, int problem_size, float cooling_rate, int ti) {
    std::string file_path = "C:\\Users\\kubap\\Desktop\\PEA2\\GA WYNIKI\\" + std::to_string(cooling_rate) + "_" +
                            std::to_string(problem_size) + ".csv";

    std::ofstream file(file_path);
    if(!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku!";
        return;
    }

    int i = 0;

    file << "czas [s];koszt\n";

    for(float cost : cost_evolution) {
        file << ti * i << ";" << cost << "\n";
        i++;
    }

    file.close();
}