#include <fstream>
#include "FileManager.h"

//czyta graf z pliku .txt i zwraca go w obu reprezentacjach
std::tuple<GraphList, GraphMatrix> FileManager::loadGraph() {
    std::ifstream file;
    std::string filePath;

    while(true) { //testuje ścieżke do pliku (sprawdza, czy istnieje)
        std::cout<<"Podaj sciezke do pliku:\n";
        std::cin>>filePath;

        file.open(filePath.c_str());
        if (file.is_open()) {
            break;
        }else {
            std::cout<<"Plik nie istnieje!\n";
        }
    }

    //czyta ilość wierzchołków i krawędzi
    int no_of_edges, no_of_vertexes;
    file>>no_of_edges>>no_of_vertexes;

    //tworzy obiekty grafów
    GraphList graph_l(no_of_vertexes, no_of_edges);
    GraphMatrix graph_m(no_of_vertexes, no_of_edges);

    //czyta po kolei krawędzie i dodaje do grafów
    int u, v, weight;
    for(int i = 0; i < no_of_edges; i++) {
        file>>u>>v>>weight;
        graph_l.newEdge(u, v, weight);
        graph_m.newEdge(u, v, i, weight);
    }

    file.close();

    return {graph_l, graph_m};
}

//zapisuje graf w pliku .txt
void FileManager::saveGraph(const GraphMatrix& graph) {
    std::ofstream file;
    std::string filePath;

    //testuje ścieżke (sprawdza, czy plik nie istnieje)
    while(true) {
        std::cout<<"Podaj sciezke do pliku:\n";
        std::cin>>filePath;

        std::ifstream test(filePath.c_str());
        if(test.good()) {
            std::cout<<"Podany plik już istnieje!\n";
            test.close();
        }else {
            file.open(filePath.c_str());
            break;
        }
    }

    //zapisuje ilość wierzchołków, krawędzi
    file<<graph.no_of_edges<<" "<<graph.no_of_vertexes<<std::endl;

    //zapisuje krawędzie
    for(int i = 0; i < graph.no_of_edges; i++) {
        int u, v, weight; //szuka krawędzi tak samo jak pobieranie tablicy krawędzi
        for(int j = 0; j < graph.no_of_vertexes; j++) {
            if(graph.matrix[j][i] > 0) {
                u = j;
            }else if(graph.matrix[j][i] < 0) {
                v = j;
            }
        }
        weight = graph.edge_weights[i];

        file<<u<<" "<<v<<" "<<weight<<std::endl;
    }

    file.close();
    std::cout<<"Zapisano graf\n";
}