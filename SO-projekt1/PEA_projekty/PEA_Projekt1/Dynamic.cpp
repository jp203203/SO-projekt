#include <vector>
#include "Dynamic.h"

//kopiuje macierz kosztów
int** Dynamic::copyCostMatrix(int** cost_matrix, int side_length) {
    int** matrix_copy = new int*[side_length];

    for(int i = 0; i < side_length; i++) {
        matrix_copy[i] = new int[side_length];
        for(int j = 0; j < side_length; j++) {
            matrix_copy[i][j] = cost_matrix[i][j];
        }
    }

    return matrix_copy;
}

//rekurencyjnie znajduje rozwiązania częściowe problemu
int Dynamic::findShortestDist(int position, int visited_mask, int** dist_matrix, int** sub_dists, int** parents, int no_of_cities) {

    //sprawdzenie, czy odwiedzono wszystkie miasta
    if(visited_mask == (1 << no_of_cities) - 1) {
        return dist_matrix[position][0]; //jeżeli tak, zwraca odległość od rozpatrywanego miasta do miasta początkowego
    }

    //sprawdzenie, czy odległość częściowa jest już obliczona
    if(sub_dists[position][visited_mask] != -1) {
        return sub_dists[position][visited_mask]; //jeżeli tak, zwraca ją
    }

    //jeżeli nie, należy ją obliczyć
    int min_dist = INT_MAX; //najkrótsza odległość w podproblemie
    int best_city = -1; //najlepsze miasto (będące "ostatnim" w zbiorze odwiedzonych)

    for(int i = 0; i < no_of_cities; i++) {
        //sprawdzanie, czy miasto nie zostało jeszcze odwiedzone za pomocą iloczynu bitowego
        if((visited_mask & (1 << i)) == 0) {
            int new_dist = dist_matrix[position][i] + findShortestDist(i, visited_mask | (1 << i), dist_matrix, sub_dists, parents, no_of_cities);
            if(new_dist < min_dist) {
                min_dist = new_dist;
                best_city = i;
            }
        }
    }

    parents[position][visited_mask] = best_city;
    return sub_dists[position][visited_mask] = min_dist;
}

//algorytm opiera swoje działanie na maskach binarnych, w której każdy bit reprezentuje odwiedzone miasto
//przykładowo, dla maski ...0011 (system N10: 3) odwiedzone bedą miasta o indeksach 0 oraz 1
//cała maska maska binarna reprezentuje zbiór odwiedzonych miast

void Dynamic::findTourDynamic(const Graph &graph, bool print_result) {
    int no_of_cities = graph.no_of_cities;
    int** dist_matrix = copyCostMatrix(graph.cost_matrix, no_of_cities);

    //stworzenie tablicy częściowych odległości oraz pomocniczej tablicy rodziców
    //wymiary tablic to n (l. miast) x 2^n
    //(np. dla n = 4, podtablice przechowują wartości od 0000 do 1111 w systemie dwójkowym - różne kombinacje miast)
    int** sub_dists = new int*[no_of_cities];
    int** parents = new int*[no_of_cities];

    for(int i = 0; i < no_of_cities; i++) {
        sub_dists[i] = new int[1 << no_of_cities];
        parents[i] = new int[1 << no_of_cities];
        for(int j = 0; j < 1 << no_of_cities; j++) {
            sub_dists[i][j] = -1;
            parents[i][j] = -1;
        }
    }

    int shortest_dist = findShortestDist(0, 1, dist_matrix, sub_dists, parents, no_of_cities);

    if(print_result) {
        printTour(parents, shortest_dist, no_of_cities);
    }

    //usuwanie tablic
    for(int i = 0; i < no_of_cities; i++) {
        delete[] dist_matrix[i];
        delete[] sub_dists[i];
        delete[] parents[i];
    }

    delete[] dist_matrix;
    delete[] sub_dists;
    delete[] parents;
}

//wyświetla optymalną trasę śledząc wartości w tablicy parents
void Dynamic::printTour(int** parents, int shortest_dist, int no_of_cities) {
    //na początku należy wyznaczyć ścieżkę
    int visited_mask = 1;
    int position = 0;
    int index = 0;
    int* tour = new int[no_of_cities];

    while(true) {
        tour[index] = position;
        int next_position = parents[position][visited_mask];
        if(next_position == -1) break;
        visited_mask = visited_mask | (1 << next_position);
        position = next_position;
        index++;
    }

    std::cout << "Najlepszy dystans: " << shortest_dist << "\n";
    std::cout<<"Przebyta trasa: ";
    for(int i = 0; i < no_of_cities + 1; i++) {
        if(i < no_of_cities) {
            std::cout << tour[i] << " -> ";
        } else {
            std::cout<<tour[0]<<"\n";
        }
    }

    delete[] tour;
}
