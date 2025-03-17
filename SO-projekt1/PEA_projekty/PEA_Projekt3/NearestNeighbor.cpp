#include "NearestNeighbor.h"

//szukanie rozwiązania za pomocą metody zachłannej (najbliższego sąsiada)
void NearestNeighbor::findNNSolution(const Graph &graph) {
    int best_solution = INT_MAX;
    std::vector<int> best_tour;

    //rozpatrywanie wszystkich wierzchołków startowych
    for(int start = 0; start < graph.no_of_cities; start++) {
        std::vector<int> partial_tour = findNNPartial(start, graph.graph_matrix, graph.no_of_cities);
        int partial_solution = calculateDistance(partial_tour, graph.graph_matrix, graph.no_of_cities);

        if(partial_solution < best_solution) { //wybranie najlepszego rozwiązania spośród wszystkich startów
            best_solution = partial_solution;
            best_tour = partial_tour;
        }
    }

    printSolution(best_tour, best_solution, graph.no_of_cities); //wyświetla wynik
}

//znajdowanie pojedynczego rozwiązania
std::vector<int> NearestNeighbor::findNNPartial(int start, int **graph_matrix, int no_of_cities) {
    std::vector<int> found_tour;
    std::vector<bool> visited_cities(no_of_cities);
    fill(visited_cities.begin(), visited_cities.end(), false);
    int visited_counter = 0;

    int current_city = start;
    found_tour.push_back(current_city);
    visited_cities[current_city] = true;
    visited_counter++;

    while(visited_counter < no_of_cities) {
        int shortest_dist = INT_MAX; //szukanie najbliższego miasta
        int best_candidate = -1;
        for(int city = 0; city < no_of_cities; city++) {
            if(visited_cities[city]) continue;

            if(graph_matrix[current_city][city] < shortest_dist) {
                shortest_dist = graph_matrix[current_city][city];
                best_candidate = city;
            }
        }
        //dodanie najbliższego miasta do wektora oraz wybranie go jako następne rozpatrywane miasto
        current_city = best_candidate;
        found_tour.push_back(current_city);
        visited_cities[current_city] = true;
        visited_counter++;
    }

    return found_tour;
}

//obliczanie trasy na podstawie macierzy kosztów grafu
int NearestNeighbor::calculateDistance(const std::vector<int>& tour, int **graph_matrix, int no_of_cities) {
    int distance = 0;

    for(int i = 0; i < no_of_cities; i++) {
        distance += graph_matrix[tour[i]][tour[(i + 1) % no_of_cities]];
    }

    return distance;
}

//wyświetlenie rozwiązania
void NearestNeighbor::printSolution(const std::vector<int>& solution, int distance, int no_of_cities) {
    std::cout<<"Rozwiazanie dla metody najblizszego sasiada:\n";
    std::cout<<"Dlugosc trasy: "<<distance<<"\n";
    std::cout<<"Trasa:\n";
    std::cout<<solution[0];
    for(int i = 1; i < no_of_cities + 1; i++) { //cykl kompletny z zapętleniem
        std::cout<<" -> "<<solution[i % no_of_cities];
    }
    std::cout<<"\n";
}