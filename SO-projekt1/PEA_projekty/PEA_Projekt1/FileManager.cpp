#include "FileManager.h"

//ładuje graf z pliku .txt
Graph FileManager::loadGraph() {
    std::ifstream file;
    std::string filePath;

    while(true) { //sprawdzenie, czy ścieżka istnieje
        std::cout<<"Podaj sciezke do pliku:\n";
        std::cin>>filePath;

        file.open(filePath.c_str());
        if(file.is_open()) {
            break;
        } else {
            std::cout<<"Podany plik nie istnieje!\n";
        }
    }

    int no_of_cities;


    file>>no_of_cities;

    Graph new_graph(no_of_cities);

    int distance;
    for(int i = 0; i < no_of_cities; i++) {
        for(int j = 0; j < no_of_cities; j++) {
            file>>distance;
            new_graph.addDistance(i, j, distance);
        }
    }

    file.close();

    return new_graph;
}

//zapisuje graf do pliku .txt
void FileManager::saveGraph(const Graph &graph) {
    std::ofstream file;
    std::string filePath;

    while(true) { //sprawdzenie, czy plik nie istnieje
        std::cout<<"Podaj sciezke do pliku:\n";
        std::cin>>filePath;

        std::ifstream test(filePath.c_str());
        if(test.good()) {
            std::cout<<"Podany plik juz istnieje!\n";
            test.close();
        } else {
            file.open(filePath.c_str());
            break;
        }
    }

    file<<graph.no_of_cities<<std::endl;

    for(int i = 0; i < graph.no_of_cities; i++) {
        for(int j = 0; j < graph.no_of_cities; j++) {
            file << graph.cost_matrix[i][j] << " ";
        }
        file<<std::endl;
    }

    file.close();
    std::cout<<"Zapisano graf\n;";
}
