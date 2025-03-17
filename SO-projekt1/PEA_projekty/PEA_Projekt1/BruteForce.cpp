#include "BruteForce.h"

//obliczanie kosztu trasy
int BruteForce::calculateTour(const Graph& graph, const int* array) {
    int tour = 0;
    int length = graph.no_of_cities;

    //suma wszystkich ścieżek pomiędzy miastami
    for(int i = 0; i < length; i++) {
        tour = tour + graph.cost_matrix[array[i]][array[(i + 1) % length]];
    }

    return tour;
}

//główna funkcja znajdująca kolejne permutacje i zwracająca optymalny koszt
int BruteForce::findBest(const Graph& graph, int* array) { //użycie algorytmu Heapa do znalezienia wszystkich permutacji
    int length = graph.no_of_cities;

    int* C = new int[length];
    int* shortest_arr = new int[length];

    for(int i = 0; i < length; i++) {
        C[i] = 1; //wypełnienie tablicy kontrolnej wartościami 1 -
    }

    int shortest_dist = calculateTour(graph, array);
    std::copy(array, array + length, shortest_arr);

    //rozpoczęcie od elementu tablicy o indeksie 1 - element o indeksie 0 nie powinien zmieniać miejsca bo jest startowy
    int k = 1;
    while(k < length) {
        if(C[k] < k) {
            if(k % 2 == 1) {
                std::swap(array[1], array[k]);
            } else {
                std::swap(array[C[k]], array[k]);
            }

            int new_dist = calculateTour(graph, array);
            if(new_dist < shortest_dist) {
                shortest_dist = new_dist;
                std::copy(array, array + length, shortest_arr);
            }

            C[k]++;
            k = 1;
        } else {
            C[k] = 1;
            k++;
        }
    }

    std::copy(shortest_arr, shortest_arr + length, array);

    delete[] C;
    delete[] shortest_arr;

    return shortest_dist;
}

//wyświetlenie wyniku
void BruteForce::printTour(int* array, int tour_dist, int length) {
    std::cout << "Najlepszy dystans: " << tour_dist << "\n";
    std::cout<<"Przebyta trasa: ";
    for(int i = 0; i < length + 1; i++) {
        if(i < length) {
            std::cout<<array[i]<<" -> ";
        } else {
            std::cout<<array[0]<<"\n";
        }
    }
}

//rozpoczęcie działania algorytmu
void BruteForce::findTourBF(const Graph& graph, bool print_result) {
    int length = graph.no_of_cities;
    int* array = new int[length];

    for(int i = 0; i < length; i++) {
        array[i] = i;
    }

    int best_dist = findBest(graph, array);

    if(print_result) {
        printTour(array, best_dist, length);
    }

    delete[] array;
}