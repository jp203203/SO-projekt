#include "Interface.h"

using namespace std;

//obiekt interfejsu przechowuje graf oraz parametry, żeby nie musieć wpisywać ich od nowa za każdym razem
Interface::Interface(FileManager fm, NearestNeighbor nn, SimAnnealing sa, TabuSearch ts, GeneticAlgorithm ga)
   :graph(0) {
    file_manager = fm;
    nearest_neighbor = nn;
    simulated_annealing = sa;
    tabu_search = ts;
    genetic_algorithm = ga;

    timeout_s = -1;
    cooling_factor = -1;
    crossover_rate = -1;
    mutation_rate = -1;
    population_size = -1;
}

//ekran menu, z roznymi opcjami do wyboru
void Interface::menuScreen() {
    while(graph.no_of_cities == 0) { //na początku wymuszenie podania jakiegoś grafu
        loadFileScreen();
    }

    while(true) {
        system("cls");
        displayParameters();
        cout<<endl;
        if(graph.no_of_cities <= 15) { //dla odpowiednio małych problemów, graf jest wyświetlany w postaci macierzowej
            graph.displayGraphMatrix();
        }
        nearest_neighbor.findNNSolution(graph); //szukanie najlepszego rozwiązania metodą zachłanną

        cout<<"Wybierz opcje:\n"
            <<"1. Wprowadz parametry\n"
            <<"2. Uruchom algorytm\n"
            <<"3. Wczytaj nowy graf\n"
            <<"4. Wczytaj trase i wyswietl wynik dla grafu\n"
            <<"5. Zakoncz program\n";

        int option_choice = optionInput(4);

        switch(option_choice) {
            case 1:
                addParametersScreen();
                break;
            case 2:
                if(timeout_s <= 0) { //nie można odpalić żadnego algorytmu bez kryterium stopu
                    cout<<"Nie podano kryterium stopu!";
                    system("pause");
                } else {
                    runAlgorithmScreen();
                }
                break;
            case 3:
                loadFileScreen();
                break;
            case 4:
                loadTourScreen();
                break;
            case 5:
                return;
            default:
                break;
        }
    }
}

//ekran ładowania pliku z grafem
void Interface::loadFileScreen() {
    system("cls");

    string file_path;
    ifstream file;

    cout<<"Podaj sciezke do pliku:\n";
    cin>>file_path;

    file.open(file_path.c_str());
    if(file.is_open()) { //jeżeli plik istnieje
        file.close(); //zamknij plik, wygeneruj graf
        graph = file_manager.readATSPFile(file_path);
        atsp_file_name = extractNameFromPath(file_path); //wyciąga nazwę pliku ze ścieżki
    } else {
        cout<<"Podany plik nie istnieje!\n";
        system("pause");
    }
}

//ekran wczytywania trasy
void Interface::loadTourScreen() {
    system("cls");

    string file_path;
    ifstream file;
    cout<<"Podaj sciezke do pliku:\n";
    cin>>file_path;

    file.open(file_path.c_str());
    if(file.is_open()) { //analogicznie jak w poprzedniej funkcji, sprawdza czy ścieżka istnieje
        file.close();
        vector<int> loaded_tour = file_manager.readTourFile(file_path, graph.no_of_cities);
        if(!loaded_tour.empty()) { //jeżeli zwrócony zbiór miast pusty, to znaczy że był błąd przy wczytywaniu
            printTour(loaded_tour, graph.graph_matrix, graph.no_of_cities); //jeżeli nie, wyświetl trasę
        }
    } else {
        cout<<"Podany plik nie istnieje!\n";
    }
    system("pause");
}

//wyświetla parametry dla algorytmów
void Interface::displayParameters() {
    //dla wartości początkowych (-1) wyświetla parametry jako nieokreślone
    cout<<"Kryterium stopu: ";
    if(timeout_s == -1) {
        cout<<"nie okreslono\n";
    } else {
        cout<<timeout_s<<" s\n";
    }
    cout<<"\n[SYMULOWANE WYZARZENIE]\n";
    cout<<"Wspolczynnik chlodzenia: ";
    if(cooling_factor == -1) {
        cout<<"nie okreslono\n";
    } else {
        cout<<cooling_factor<<"\n";
    }
    cout<<"\n[ALGORYTM GENETYCZNY]\n";
    cout<<"Wspolczynnik krzyzowania: ";
    if(crossover_rate == -1) {
        cout<<"nie okreslono\n";
    } else {
        cout<<crossover_rate<<"\n";
    }
    cout<<"Wspolczynnik mutacji: ";
    if(mutation_rate == -1) {
        cout<<"nie okreslono\n";
    } else {
        cout<<mutation_rate<<"\n";
    }
    cout<<"Rozmiar populacji: ";
    if(population_size == -1) {
        cout<<"nie okreslono\n";
    } else {
        cout<<population_size<<"\n";
    }
    cout<<"\nWczytany graf: "<<atsp_file_name<<"\n"; //wyświetla również nazwę wczytanego pliku
}

//ekran dodawania parametrów
void Interface::addParametersScreen() {
    system("cls");

    cout<<"Wybierz opcje:\n"
        <<"1. Podaj kryterium stopu (w sekundach)\n"
        <<"2. Podaj wspolczynnik chlodzenia\n"
        <<"3. Podaj wspolczynnik krzyzowania\n"
        <<"4. Podaj wspolczynnik mutacji\n"
        <<"5. Podaj rozmiar populacji\n";

    int parameter_choice = optionInput<int>(5);
    cout<<"Podaj wartosc:\n";
    switch(parameter_choice) {
        case 1:
            timeout_s = optionInput<int>(0, 30); //możliwość wyboru kryterium czasu bez limitu
            break;
        case 2:
            cooling_factor = optionInput<float>(1, 0); //współczynnik chłodzenia od 0 do 1
            break;
        case 3:
            crossover_rate = optionInput<float>(1, 0);
            break;
        case 4:
            mutation_rate = optionInput<float>(1, 0);
            break;
        case 5:
            population_size = optionInput<int>(0, 10);
        default:
            break;
    }
}

//ekran odpalania algorytmów
void Interface::runAlgorithmScreen() {
    while(true) {
        NeighborhoodMethod method;

        cout<<"Wybierz algorytm:\n"
            <<"1. Tabu search - sasiedztwo przez zamiane miast w trasie\n"
            <<"2. Tabu search - sasiedztwo przez odwrocenie sciezki w trasie\n"
            <<"3. Tabu search - sasiedztwo przez wstawienie miasta w inne miejsce\n"
            <<"4. Symulowane wyzarzenie\n"
            <<"5. Algorytm genetyczny\n"
            <<"6. Powrot\n";
        int algorithm_option = optionInput<int>(6);

        //nie można odpalić algorytmów SW i GA bez podania odpowiednich parametrów
        if(algorithm_option == 4 && cooling_factor == -1) {
            cout << "Nie podano wspolczynnika chlodzenia!\n";
            continue;
        } else if(algorithm_option == 5 && (mutation_rate == -1 || crossover_rate == -1 || population_size == -1)) {
            cout << "Nie podano wspolczynnika mutacji, krzyzowania lub rozmiaru populacji!\n";
            continue;
        } else if(algorithm_option == 6) {
            break;
        } else if(1 <= algorithm_option && algorithm_option <= 3) { //wybiera odpowiednią metodę doboru sąsiedztwa dla TS
            switch(algorithm_option) {
                case 1:
                    method = NeighborhoodMethod::SWAP;
                    break;
                case 2:
                    method = NeighborhoodMethod::REVERSE;
                    break;
                case 3:
                    method = NeighborhoodMethod::INSERT;
                    break;
            }
        }

        cout<<"Ile wykonac powtorzen?\n";
        int repetitions = optionInput<int>(0);

        if(algorithm_option < 5) {
            runSAOrTSScreen(repetitions, algorithm_option, method);
        } else if(algorithm_option == 5) {
            runGAScreen(repetitions);
        }
    }
}

//ekstrakcja nazwy pliku ze ścieżki pliku - do wyświetlenia w menu oraz użyta do zapisu pliku z trasą
string Interface::extractNameFromPath(string file_path) {
    string file_name = file_path;

    int path_size = file_name.size();
    int last_slash_index = -1;
    for(int i = 0; i < path_size; i++) {
        if(file_name[i] == char(92)) { //szuka ostatniego ukośnika
            last_slash_index = i;
        }
    }

    if(last_slash_index != -1) { //"ucina" ścieżkę z ciągu znaków
        file_name.erase(file_name.begin(), file_name.begin() + last_slash_index + 1);
    }

    return file_name;
}

//funkcja sprawdzająca, czy wpisywane dane są poprawne pod względem typu danych jak i ustalonych limitów
//jeżeli limit ustawiony na 0, to tak naprawdę brak limitu
//dolny limit to domyślnie 1, można zmienić
template <typename T> T Interface::optionInput(T limit, T lower_limit) {
    T option;

    while(!(cin>>option) || (option > limit && limit != 0) || option < lower_limit) {
        cout << "Niepoprawna opcja! Wpisz inna wartosc:\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return option;
}

//wyświetlanie trasy, implementuje obliczanie dystansu z metody zachłannej
void Interface::printTour(vector<int> tour, int **graph_matrix, int no_of_cities) {
    std::cout<<"Dlugosc trasy: "<<nearest_neighbor.calculateDistance(tour, graph_matrix, no_of_cities)<<"\n";
    std::cout<<"Trasa:\n";
    std::cout<<tour[0];
    for(int i = 1; i < no_of_cities + 1; i++) {
        std::cout<<" -> "<<tour[i % no_of_cities];
    }
    std::cout<<"\n";
}

//ekran odpalania algorytmów symulowanego wyżarzenia oraz tabu search
void Interface::runSAOrTSScreen(int repetitions, int alg_option, NeighborhoodMethod method) {
    std::vector<int> best_evolution; //przechowuje najlepsze rozwiązanie z serii rozwiązań
    int best_distance = INT_MAX;
    std::vector<int> cost_evolution;
    int distance = 0;

    std::cout<<"Podaj przedzial czasowy badania zmiany kosztu (w sekundach):\n";
    auto time_interval = optionInput<float>(0, 0);

    for(int i = 0; i < repetitions; i++) {
        if(1 <= alg_option && alg_option <= 3) {
            auto result = tabu_search.findTabuSolution(graph.graph_matrix, graph.no_of_cities,
                                                       timeout_s, method, (graph.no_of_cities / 10) * 10,
                                                       300, time_interval);
            cost_evolution = result.first;
            distance = result.second;
        } else if(alg_option == 4) {
            auto result = simulated_annealing.findAnnealingSolution(graph.graph_matrix,
                                                                    graph.no_of_cities, timeout_s, cooling_factor,
                                                                    time_interval);
            cost_evolution = result.first;
            distance = result.second;
        }

        if(distance < best_distance) {
            best_evolution = cost_evolution;
            best_distance = distance;
        }
    }

    if(1 <= alg_option && alg_option <= 3) {
        file_manager.saveCSVFile_TS(best_evolution, graph.no_of_cities, alg_option, time_interval);
    } else if(alg_option == 4) {
        file_manager.saveCSVFile_SA(best_evolution, graph.no_of_cities, cooling_factor, time_interval);
    }

    //na koniec istnieje możliwość zapisania najlepszego wyniku z serii jako ciąg miast w odpowiedniej kolejności
    cout<<"Zapisac najlepszy wynik?\n"
        <<"1. Tak\n"
        <<"2. Nie\n";
    int save_option = optionInput<int>(2);

    if(save_option == 1) {
        file_manager.generateTourFile(atsp_file_name, graph.no_of_cities, best_evolution, alg_option, cooling_factor);
    }
}

//ekran odpalania algorytmu genetycznego
void Interface::runGAScreen(int repetitions) {
    std::vector<float> cost_evolution;

    int distance;
    int best_distance = INT_MAX;

    std::cout<<"Podaj metode krzyzowania:\n"
             <<"1. Krzyzowanie OX (Order Crossover)\n"
             <<"2. Krzyzowanie SCX (Sequential Constructive Crossover)\n";
    int crossover_option = optionInput<int>(2);

    std::cout<<"Podaj metode mutacji:\n"
             <<"1. Zamiana dwoch miast\n"
             <<"2. Wstawienie miasta za inne miasto\n";
    int mutation_option = optionInput<int>(2);

    std::cout<<"Podaj przedzial czasowy badania zmiany kosztu (w sekundach):\n";
    int time_interval = optionInput<int>(0);

    for(int i = 0; i < repetitions; i++) {
        auto result = genetic_algorithm.findGeneticSolution(graph.graph_matrix, graph.no_of_cities, population_size,
                                                            timeout_s, mutation_rate, crossover_rate, mutation_option,
                                                            crossover_option, time_interval);

        distance = result.first;
        cout<<"Ostateczny koszt dla "<<i<<". uruchomienia: "<<distance<<"\n";
        float best_average = numeric_limits<float>::max();

        for(float j : result.second) {
            if(j < best_average) {
                best_average = j;
            }
        }
        cout<<fixed<<setprecision(2);
        cout<<"Najlepszy sredni koszt dla "<<i<<". uruchomienia: "<<best_average<<"\n";
        if(distance < best_distance) {
            best_distance = distance;
            cost_evolution = result.second;
        }
    }
    cout<<"Najlepszy koszt: "<<best_distance<<"\n";
    cout<<"Ewolucja kosztow: ";
    for(int i = 0; i < cost_evolution.size(); i++) {
        cout<<cost_evolution[i];
        if(i != cost_evolution.size() - 1) {
            cout<<", ";
        }
    }
    cout<<"\n";

    file_manager.saveCSVFile_GA(cost_evolution, crossover_option, mutation_option, mutation_rate, crossover_rate,
                                population_size, time_interval);
}