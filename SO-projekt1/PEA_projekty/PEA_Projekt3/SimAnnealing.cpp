#include "SimAnnealing.h"

SimAnnealing::SimAnnealing() {
    timer = Timer(); //pomiar czasu do pilnowania kryterium stopu oraz rejestrowania czasu najlepszego rozwiązania
}

//generowanie pierwszej, losowej trasy
std::vector<int> SimAnnealing::genInitTour(int no_of_cities, std::mt19937 gen) {
    std::vector<int> new_tour(no_of_cities);
    for(int i = 0; i < no_of_cities; i++) {
        new_tour[i] = i;
    }

    std::shuffle(new_tour.begin(), new_tour.end(), gen);
    return new_tour;
}

//odwrócenie ścieżki pomiędzy dwoma miastami w trasie, działa analogicznie do funkcji z Tabu Search
//różnica jest taka, że w tej funkcji oba miasta są losowane, zamiast podawane jako argumenty
std::vector<int> SimAnnealing::reversePath(std::vector<int> tour, int no_of_cities, std::mt19937 gen) {
    std::uniform_int_distribution<> dist(0, no_of_cities - 1);
    int first_city = dist(gen);
    int second_city = dist(gen);
    while(first_city == second_city) {
        second_city = dist(gen);
    }

    std::vector<int> new_tour = tour;
    int reversed_cities = (first_city < second_city) ? second_city - first_city + 1 : no_of_cities - (first_city - second_city) + 1;

    for(int i = 1; i <= reversed_cities / 2; i++) {
        swap(new_tour[first_city % no_of_cities], new_tour[second_city % no_of_cities]);

        first_city = (first_city + 1) % no_of_cities;
        second_city = (second_city - 1 + no_of_cities) % no_of_cities;
    }

    return new_tour;
}

//wstawienie ścieżki między dwoma miastami do nowego miejsca w trasie
std::vector<int> SimAnnealing::insertPath(std::vector<int> tour, int no_of_cities, std::mt19937 gen) {
    std::vector<int> new_tour(no_of_cities);
    int max_path_len = (no_of_cities * 2) / 3;

    std::uniform_int_distribution<> dist(0, no_of_cities - 1);
    //znalezienie ścieżki
    int first_city = dist(gen);
    int second_city = dist(gen);
    while(first_city == second_city || abs(second_city - first_city) > max_path_len) {
        second_city = dist(gen);
    }
    if(first_city > second_city) swap(first_city, second_city);

    //następnie, znalezienie nowego miejsca dla wyznaczonej ścieżki
    int third_city = dist(gen);
    while(third_city >= first_city && third_city <= second_city) {
        third_city = dist(gen);
    }

    int current_city = 0;
    for(int i = 0; i < no_of_cities; i++) {
        if(i >= first_city && i <= second_city) { //pomijanie miast ze ścieżki
            continue;
        }
        new_tour[current_city] = tour[i];
        current_city++;

        if(i == third_city) { //wstawienie miast ze ścieżki dopiero, gdy osiągnięte jest nowe miejsce
            for(int j = first_city; j <= second_city; j++) {
                new_tour[current_city] = tour[j];
                current_city++;
            }
        }
    }

    return new_tour;
}

//obliczanie kosztu trasy
int SimAnnealing::calculateDistance(std::vector<int> tour, int no_of_cities, int **graph_matrix) {
    int distance = 0;
    for(int i = 0; i < no_of_cities; i++) {
        distance += graph_matrix[tour[i]][tour[(i + 1) % no_of_cities]];
    }

    return distance;
}

//wyświetlanie wyniku, razem z czasem znalezienia najlepszego rozwiązania oraz temperaturą końcową
void SimAnnealing::printSolution(std::vector<int> solution, int distance, int no_of_cities, double time, double end_temp) {
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
    std::cout<<std::fixed<<std::showpoint<<std::setprecision(std::numeric_limits<float>::digits10 + 1);
    std::cout<<"\nTemperatura koncowa: "<<end_temp<<"\n";
    std::cout<<"Wartosc wyrazenia exp(-1/Tk): "<<exp(-1/end_temp)<<"\n";
}

//główna funkcja algorytmu
std::pair<std::vector<int>, int> SimAnnealing::findAnnealingSolution(int **graph_matrix, int no_of_cities, int timeout_s,
                                                                     float cooling_factor, float time_interval) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> neighbor_choice(0, 1);
    std::uniform_real_distribution<> random(0, 1);

    std::vector<int> current_solution = genInitTour(no_of_cities, gen); //rozpoczęcie od losowej trasy
    int current_distance = calculateDistance(current_solution, no_of_cities, graph_matrix);
    std::vector<int> cost_evolution;
    int best_distance = current_distance;

    //obliczenie temperatury początkowej
    double temp = (10 * no_of_cities * (360 / timeout_s)) / log(no_of_cities * timeout_s);
    double best_solution_time = 0;

    double last_cooling_time = 0.0; //odmierzanie czasu od ostatniego chłodzenia
    float next_measure = time_interval;

    cost_evolution.push_back(best_distance);

    timer.start();
    while(true) {
        timer.stop();
        if(timer.getTime() >= next_measure) {
            cost_evolution.push_back(best_distance);
            next_measure += time_interval;
        }

        if(timer.getTime() >= timeout_s) break; //sprawdzanie, czy osiągnięto kryterium stopu

        std::vector<int> neighbor_tour;
        if(neighbor_choice(gen) == 0) { //losowo wybierana jedna z metod znajdowania kolejnego sąsiada
            neighbor_tour = reversePath(current_solution, no_of_cities, gen);
        } else {
            neighbor_tour = insertPath(current_solution, no_of_cities, gen);
        }
        int neighbor_distance = calculateDistance(neighbor_tour, no_of_cities, graph_matrix);
        int delta = neighbor_distance - current_distance;

        //jeżeli wynik dla sąsiada jest lepszy niż obecny, to przyjmujemy go jako obecny wynik
        //jeżeli nie, to obliczane jest prawdopodobieństwo przyjęcia go
        if(delta <= 0 || exp(-delta / temp) > random(gen)) {
            current_solution = neighbor_tour;
            current_distance = neighbor_distance;

            if(current_distance < best_distance) {
                best_distance = current_distance;

                timer.stop();
                best_solution_time = timer.getTime();
            }
        }

        timer.stop();
        double elapsed_time = timer.getTime();
        //co sekundę następuje zmiana temperatury zgodnie ze współczynnikiem chłodzenia
        if(elapsed_time - last_cooling_time >= 1) {
            temp *= cooling_factor;
            last_cooling_time = elapsed_time;
        }
    }

    //printSolution(best_solution, best_distance, no_of_cities, best_solution_time, temp);

    return {cost_evolution, best_distance};
}