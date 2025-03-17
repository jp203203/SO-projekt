#include "Graph.h"

Graph::Graph(int no_of_cities) {
    this -> no_of_cities = no_of_cities;

    cost_matrix = new int*[no_of_cities]; //macierz kosztów / reprezentacja macierzowa grafu
    for(int i = 0; i < no_of_cities; i++) {
        cost_matrix[i] = new int[no_of_cities];
        for(int j = 0; j < no_of_cities; j++) {
            if(i == j){
                cost_matrix[i][j] = -1; //wartości -1 na przekątnej
            } else {
                cost_matrix[i][j] = 0;
            }
        }
    }
}

void Graph::addDistance(int start, int dest, int distance) const {
    cost_matrix[start][dest] = distance; //ustawiany jest koszt krawędzi
}

//wyświetla graf
void Graph::displayGraph() const {
    std::cout<<"Wyswiatlanie grafu:\n";
    std::cout<<"Liczba miast: "<<no_of_cities<<"\n\n";

    for(int i = 0; i < no_of_cities; i++) {
        for(int j = 0; j < no_of_cities; j++) {
            std::cout << cost_matrix[i][j] << " ";
        }
        std::cout<<std::endl;
    }

    std::cout<<std::endl;
}