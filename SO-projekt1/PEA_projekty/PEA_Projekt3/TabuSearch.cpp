#include "TabuSearch.h"

TabuSearch::TabuSearch() {
    timer = Timer(); //odmierzanie czasu, do pilnowania kryterium stopu oraz rejestrowania czasu znalezienia rozwiązania
}

//generowanie początkowej (losowej) trasy
std::vector<int> TabuSearch::genInitTour(int no_of_cities, std::mt19937 gen) {
    std::vector<int> new_tour(no_of_cities);
    for(int i = 0; i < no_of_cities; i++) {
        new_tour[i] = i;
    }

    std::shuffle(new_tour.begin(), new_tour.end(), gen);
    return new_tour;
}

//odwrócenie ścieżki pomiędzy dwoma miastami w trasie
std::vector<int> TabuSearch::reversePath(std::vector<int> tour, int first_city, int second_city, int no_of_cities) {
    std::vector<int> new_tour = tour;
    //obliczenie ilości miast, które będą odwrócone
    int reversed_cities = (first_city < second_city) ? second_city - first_city + 1 : no_of_cities - (first_city - second_city) + 1;

    for(int i = 1; i <= reversed_cities / 2; i++) {
        swap(new_tour[first_city % no_of_cities], new_tour[second_city % no_of_cities]);

        first_city = (first_city + 1) % no_of_cities;
        second_city = (first_city - 1 + no_of_cities) % no_of_cities;
    }

    return new_tour;
}

//wstawienie miasta w inne miejsce w trasie
std::vector<int> TabuSearch::insertCity(std::vector<int> tour, int insert_from, int insert_to, int no_of_cities) {
    std::vector<int> new_tour(no_of_cities);

    int current_city = 0;
    for(int i = 0; i <= no_of_cities; i++) {
        if(i == insert_from) continue; //pominięcie miasta, jeżeli jest ono tym wstawianym
        new_tour[current_city] = tour[i];
        current_city++;

        if(i == insert_to) { //następnie dodanie go po mieście, po którym należy je wstawić
            new_tour[current_city] = tour[insert_from];
            current_city++;
        }
    }

    return new_tour;
}

//przeszukanie sąsiedztwa za pomocą metody zamiany elementów
std::pair<std::vector<int>, std::pair<int, int>> TabuSearch::neighborhoodSwap(const std::vector<int>& current_solution, int** graph_matrix, int no_of_cities, int best_distance) {
    int best_neighbor_dist = INT_MAX;
    std::vector<int> best_neighbor; //przechowywanie najlepszego sąsiada
    std::pair<int, int> best_move;

    //funkcja rozważa wszystkie możliwości zamiany
    for(int i = 0; i < no_of_cities; i++) {
        for(int j = i + 1; j < no_of_cities; j++) {

            std::vector<int> neighbor_solution = current_solution;
            std::swap(neighbor_solution[i], neighbor_solution[j]);
            int neighbor_distance = calculateDistance(neighbor_solution, graph_matrix, no_of_cities);
            std::pair<int, int> move = {i, j};

            //sprawdzenie, czy wykonany ruch znajduje się na liście tabu
            //wykonanie ruchu pomimo tego, że znajduje się na liście, jeśli da on najlepszy do tej pory wynik
            if(find(tabu_list.begin(), tabu_list.end(), move) != tabu_list.end() && neighbor_distance >= best_distance) {
                continue;
            }

            if(neighbor_distance < best_neighbor_dist) {
                best_neighbor = neighbor_solution;
                best_neighbor_dist = neighbor_distance;
                best_move = move;
            }
        }
    }

    //zwrócenie najlepszego sąsiada oraz najlepszego ruchu
    return {best_neighbor, best_move};
}

//przeszukanie sąsiedztwa za pomocą metody odwrócenia kolejności
std::pair<std::vector<int>, std::pair<int, int>> TabuSearch::neighborhoodReverse(const std::vector<int>& current_solution, int **graph_matrix, int no_of_cities, int best_distance) {
    int best_neighbor_dist = INT_MAX;
    std::vector<int> best_neighbor;
    std::pair<int, int> best_move;

    //funkcja rozważa wszystkie możliwości odwrócenia kierunku pomiędzy dwoma punktami
    //poza zakresami pętli oraz sposobem znajdowania sąsiedztwa, funkcja działa analogicznie do poprzedniej
    for(int i = 0; i < no_of_cities; i++) {
        for(int j = 0; j < no_of_cities; j++) {
            if(i == j) continue;

            std::vector<int> neighbor_solution = reversePath(current_solution, i, j, no_of_cities);
            int neighbor_distance = calculateDistance(neighbor_solution, graph_matrix, no_of_cities);
            std::pair<int, int> move = {i, j};

            if(find(tabu_list.begin(), tabu_list.end(), move) != tabu_list.end() && neighbor_distance >= best_distance) {
                continue;
            }

            if(neighbor_distance < best_neighbor_dist) {
                best_neighbor = neighbor_solution;
                best_neighbor_dist = neighbor_distance;
                best_move = move;
            }
        }
    }

    return {best_neighbor, best_move};
}

//przeszukanie sąsiedztwa za pomocą metody wstawienia miasta
std::pair<std::vector<int>, std::pair<int, int>> TabuSearch::neighborhoodInsert(const std::vector<int> &current_solution, int **graph_matrix, int no_of_cities, int best_distance) {
    int best_neighbor_dist = INT_MAX;
    std::vector<int> best_neighbor;
    std::pair<int, int> best_move;

    for(int i = 0; i < no_of_cities; i++) {
        for(int j = 0; j < no_of_cities; j++) {
            if(i == j || i - j == 1) continue;

            std::vector<int> neighbor_solution = insertCity(current_solution, i, j, no_of_cities);
            int neighbor_distance = calculateDistance(neighbor_solution, graph_matrix, no_of_cities);
            std::pair<int, int> move = {i, j};

            if(find(tabu_list.begin(), tabu_list.end(), move) != tabu_list.end() && neighbor_distance >= best_distance) {
                continue;
            }

            if(neighbor_distance < best_neighbor_dist) {
                best_neighbor = neighbor_solution;
                best_neighbor_dist = neighbor_distance;
                best_move = move;
            }
        }
    }

    return {best_neighbor, best_move};
}

//obliczanie długości trasy
int TabuSearch::calculateDistance(std::vector<int> tour, int **graph_matrix, int no_of_cities) {
    int distance = 0;
    for(int i = 0; i < no_of_cities; i++) {
        distance += graph_matrix[tour[i]][tour[(i + 1) % no_of_cities]];
    }

    return distance;
}

//wyświetlenie wyniku - również wyświetla czas znalezienia najlepszego rozwiązania
void TabuSearch::printSolution(std::vector<int> solution, int distance, int no_of_cities, double time) {
    std::cout<<"Znalezione rozwiazanie:\n";
    std::cout<<"Dlugosc trasy: "<<distance<<"\n";
    std::cout<<"Trasa:\n";
    std::cout<<solution[0];
    for(int i = 1; i < no_of_cities + 1; i++) {
        std::cout<<" -> "<<solution[i % no_of_cities];
    }
    std::cout<<"\n";
    std::cout<<std::fixed<<std::showpoint<<std::setprecision(5);
    std::cout<<"Czas znalezienia rozwiazania: "<<time<<" s\n";
}

//główna funkcja algorytmu
std::pair<std::vector<int>, int> TabuSearch::findTabuSolution(int **graph_matrix, int no_of_cities, int timeout_s,
                                                              NeighborhoodMethod method, int tabu_limit,
                                                              int diversify_point, float time_interval) {
    tabu_list.clear(); //czyszczenie listy tabu przed każdym rozpoczęciem

    std::random_device rd;
    std::mt19937 gen(rd());

    timer.start(); //rozpoczęcie odmierzania czasu

    //na początek losowa trasa
    std::vector<int> current_solution = genInitTour(no_of_cities, gen);
    int current_distance = calculateDistance(current_solution, graph_matrix, no_of_cities);

    std::vector<int> cost_evolution;
    int best_distance = current_distance;
    double best_solution_time = 0;

    float next_measure = time_interval;

    cost_evolution.push_back(best_distance);

    //licznik poprawy wyniku, służący do pilnowania diwersyfikacji
    int no_improvement_count = 0;
    while(true) {
        timer.stop();
        if(timer.getTime() >= next_measure) {
            cost_evolution.push_back(best_distance);
            next_measure += time_interval;
        }

        if(timer.getTime() >= timeout_s) {
            break; //sprawdzenie, czy kryterium stopu zostało spełnione
        }

        std::vector<int> best_neighbor;
        std::pair<int, int> best_move;

        //przeszukiwanie sąsiedztwa w zależności od wybranej metody
        switch(method) {
            case NeighborhoodMethod::SWAP:
                std::tie(best_neighbor, best_move) =
                        neighborhoodSwap(current_solution, graph_matrix, no_of_cities, best_distance);
                break;
            case NeighborhoodMethod::REVERSE:
                std::tie(best_neighbor, best_move) =
                        neighborhoodReverse(current_solution, graph_matrix, no_of_cities, best_distance);
                break;
            case NeighborhoodMethod::INSERT:
                std::tie(best_neighbor, best_move) =
                        neighborhoodInsert(current_solution, graph_matrix, no_of_cities, best_distance);
        }
        int best_neighbor_dist = calculateDistance(best_neighbor, graph_matrix, no_of_cities);

        //dekrementacja licznika, kiedy najlepszy sąsiad daje lepszy wynik niż obecne rozwiązanie
        //ma to na celu umożliwienie algorytmowi wykonania kolejnego ruchu po zmniejszeniu wyniku
        //oraz zwiększenie szansy na znalezienie lepszego rozwiązania po diwersyfikacji
        if(best_neighbor_dist < current_distance) {
            no_improvement_count--;
        }

        current_solution = best_neighbor;
        current_distance = best_neighbor_dist;

        if(current_distance < best_distance) {
            best_distance = current_distance;

            timer.stop();
            best_solution_time = timer.getTime();

            no_improvement_count = 0; //resetowanie licznika, jeżeli znaleziono nowe najlepsze rozwiązanie
        } else {
            no_improvement_count++;
        }

        tabu_list.push_back(best_move);
        if(tabu_list.size() > tabu_limit) { //pilnowanie ustalonego rozmiaru listy tabu - w programie jest to rozmiar problemu
            tabu_list.pop_front();
        }

        if(no_improvement_count == diversify_point) { //osiągnięcie punktu diwersyfikacji
            current_solution = genInitTour(no_of_cities, gen); //"reset" algorytmu - nowe losowe rozwiązanie
            current_distance = calculateDistance(current_solution, graph_matrix, no_of_cities);
            no_improvement_count = 0;
        }
    }

    //printSolution(best_solution, best_distance, no_of_cities, best_solution_time);

    return {cost_evolution, best_distance};
}