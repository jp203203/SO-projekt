#include "BnBLittle.h"

bool BnBLittle::CompareNodes::operator()(const Node& node1, const Node& node2) const {
    return node1.lower_bound > node2.lower_bound;
}

//redukcja kosztów macierzy oraz zwrot sumy redukcji
int BnBLittle::reduceCostMatrix(std::vector<std::vector<int>>& cost_matrix, int side_length, const std::vector<bool>& row_excluded, const std::vector<bool>& col_excluded) {
    int shortest_path;
    int reduction_sum = 0;

    //redukcja kosztów w wierszach
    for(int i = 0; i < side_length; i++) {
        if(row_excluded[i]) continue;
        shortest_path = INT_MAX;

        for(int j = 0; j < side_length; j++) {
            if(col_excluded[j]) continue;
            if(shortest_path > cost_matrix[i][j] && cost_matrix[i][j] != -1) {
                shortest_path = cost_matrix[i][j];
            }
        }

        if(shortest_path == INT_MAX || shortest_path == 0) { //zabezpieczenie na wypadek, gdy wszystkie wartości w wierszach to -1
            continue; //pominięcie odejmowania w wierszu jeśli najkrótsza ścieżka równa zero
        }

        reduction_sum += shortest_path;
        for(int j = 0; j < side_length; j++) {
            if(col_excluded[j]) continue;
            if(cost_matrix[i][j] != -1) {
                cost_matrix[i][j] -= shortest_path;
            }
        }
    }

    //redukcja kosztów w kolumnach
    for(int j = 0; j < side_length; j++) {
        if(col_excluded[j]) continue;
        shortest_path = INT_MAX;

        for(int i = 0; i < side_length; i++) {
            if(row_excluded[i]) continue;
            if(shortest_path > cost_matrix[i][j] & cost_matrix[i][j] != -1) {
                shortest_path = cost_matrix[i][j];
            }
        }

        if(shortest_path == INT_MAX || shortest_path == 0) {
            continue;
        }

        reduction_sum += shortest_path;
        for(int i = 0; i < side_length; i++) {
            if(row_excluded[i]) continue;
            if(cost_matrix[i][j] != -1) {
                cost_matrix[i][j] -= shortest_path;
            }
        }
    }

    return reduction_sum;
}

//znajdowanie krawędzi, według której następuje podział problemu
std::vector<int> BnBLittle::findDivision(const std::vector<std::vector<int>>& cost_matrix, int side_length, const std::vector<bool>& row_excluded, const std::vector<bool>& col_excluded) {
    //znalezienie rozszerzenia drzewa
    int biggest_theta = -1; //kara za niewybranie danego połączenia - zaczyna od -1
    std::vector<int> path(2);

    for(int i = 0; i < side_length; i++) {
        if(row_excluded[i]) continue;

        for(int j = 0; j < side_length; j++) {
            if(col_excluded[j]) continue;

            if(cost_matrix[i][j] == 0) {
                int current_pos_theta = 0;
                int second_lowest = INT_MAX;

                for(int k = 0; k < side_length; k++) { //szukanie drugiego najwyższego kosztu w wierszu
                    if(col_excluded[k] || k == j) continue;
                    if(cost_matrix[i][k] < second_lowest && cost_matrix[i][k] != -1) {
                        second_lowest = cost_matrix[i][k];
                        if(second_lowest == 0) break; //wyjście z pętli jeżeli znaleziona wartość to 0
                    }
                }
                current_pos_theta += second_lowest;
                second_lowest = INT_MAX;

                for(int k = 0; k < side_length; k++) { //szukanie drugiego najwyższego kosztu w kolumnie
                    if(row_excluded[k] || k == i) continue;
                    if(cost_matrix[k][j] < second_lowest && cost_matrix[k][j] != -1) {
                        second_lowest = cost_matrix[k][j];
                        if(second_lowest == 0) break;
                    }
                }
                current_pos_theta += second_lowest;

                if(current_pos_theta > biggest_theta) {
                    biggest_theta = current_pos_theta;
                    path[0] = i;
                    path[1] = j;
                }
            }
        }
    }
    return path;
}

//znajdowanie krawędzi tworzącej "podcykl" w podproblemie
std::vector<int> BnBLittle::findSubTour(const std::vector<int>& path, const std::vector<std::vector<int>>& included_cities) {
    std::vector<int> new_path(path); //inicjalizacja tablicy reprezentującej zespojoną trasę

    bool connection_exists = true;
    while(connection_exists) {
        connection_exists = false;
        for(const std::vector<int>& committed_path : included_cities) { //"łączy" ze sobą krawędzie "od lewej" i dodaje je do spójnej trasy
            if(committed_path[1] == new_path[0]) {
                new_path[0] = committed_path[0];
                connection_exists = true;
            }
        }
    }

    connection_exists = true;
    while(connection_exists) {
        connection_exists = false;
        for(const std::vector<int>& committed_path : included_cities) { //to samo co wyżej, tylko że teraz łączy "od prawej"
            if(committed_path[0] == new_path[1]) {
                new_path[1] = committed_path[1];
                connection_exists = true;
            }
        }
    }

    std::swap(new_path[0], new_path[1]); //zamienia początek i koniec trasy ze sobą - co daje krawędź tworzącą "podcykl"
    return new_path;
}

//sprawdzanie, czy dana krawędź tworzy "podcykl" z innymi krawędziami w rozwiązaniach podproblemu
bool BnBLittle::makesSubTour(int row_index, int col_index, const std::vector<std::vector<int>>& paths, bool all_connections) {
    std::vector<int> new_path = {row_index, col_index}; //inicjalizacja tablicy reprezentującej zespojoną trasę
    bool sub_tour_exists = false;

    if(new_path[0] == new_path[1]) { //jeżeli oba miasta to to samo miasto, zwraca wartość true
        return true;
    }

    //jeżeli którakolwiek z krawędzi kończy się lub zaczyna w tym samym mieście, zwraca true
    for(const std::vector<int>& committed_path : paths) {
        if(committed_path[0] == new_path[0] || committed_path[1] == new_path[1]) {
            return true;
        }
    }

    bool connection_exists = true;

    while(connection_exists) {
        connection_exists = false;

        for(const std::vector<int>& committed_path : paths) {
            if(committed_path[1] == new_path[0]) { //"łączy" ze sobą krawędzie "od lewej" i dodaje je do spójnej trasy
                new_path[0] = committed_path[0];

                if(new_path[0] == new_path[1]) { //jeżeli początek i koniec są tym samym miastem to istnieje "podcykl"
                    sub_tour_exists = true;
                }

                connection_exists = true;
            }
        }
    }

    connection_exists = true;

    while(connection_exists) {
        connection_exists = false;

        for(const std::vector<int>& committed_path : paths) {
            if(committed_path[0] == new_path[1]) { //to samo co wyżej, tylko że teraz łączy "od prawej"
                new_path[1] = committed_path[1];

                if(new_path[0] == new_path[1]) {
                    sub_tour_exists = true;
                }

                connection_exists = true;
            }
        }
    }
    if(sub_tour_exists && all_connections) { //jeżeli wszystkie krawędzie zostały znalezione, to cykl może powstać
        sub_tour_exists = false; //to znaczy, że nie został utworzony "podcykl" - tylko pełny cykl Hamiltona
    }

    return sub_tour_exists;
}

//utworzenie poddrzew drzewa rozwiązań
std::vector<BnBLittle::Node> BnBLittle::createSubTrees(const Node& X, int no_of_cities) {
    std::vector<Node> sub_trees;
    std::vector<int> path = findDivision(X.cost_matrix, no_of_cities, X.row_excluded, X.col_excluded); //wyznaczenie podziału
    int reduction_sum;

    //stworzenie węzła Y wykluczającego ścieżkę - prawe poddrzewo
    Node Y(no_of_cities);
    Y.cost_matrix = X.cost_matrix;
    Y.col_excluded = X.col_excluded;
    Y.row_excluded = X.row_excluded;
    Y.side_length = X.side_length;
    Y.cost_matrix[path[0]][path[1]] = -1; //brak połączenia

    reduction_sum = reduceCostMatrix(Y.cost_matrix, no_of_cities, Y.row_excluded, Y.col_excluded);
    Y.lower_bound = X.lower_bound + reduction_sum;
    Y.included_paths = X.included_paths;
    Y.omitted_paths = X.omitted_paths;
    Y.omitted_paths.push_back(path);

    sub_trees.push_back(Y);

    //stworzenie węzła Z ze ścieżką - lewe poddrzewo
    Node Z(no_of_cities);
    Z.cost_matrix = X.cost_matrix;
    Z.row_excluded = X.row_excluded;
    Z.row_excluded[path[0]] = true;
    Z.col_excluded = X.col_excluded;
    Z.col_excluded[path[1]] = true;
    Z.side_length = X.side_length - 1;
    Z.included_paths = X.included_paths;
    Z.omitted_paths = X.omitted_paths;
    if(Z.side_length != 2) {
        std::vector<int> sub_tour_connection = findSubTour(path, Z.included_paths);
        Z.cost_matrix[sub_tour_connection[0]][sub_tour_connection[1]] = -1; //należy wykluczyć połączenie tworzące "podcykl"
    }
    reduction_sum = reduceCostMatrix(Z.cost_matrix, no_of_cities, Z.row_excluded, Z.col_excluded);
    Z.lower_bound = X.lower_bound + reduction_sum;
    Z.included_paths.push_back(path);

    sub_trees.push_back(Z);

    return sub_trees;
}

//znalezienie pozostałych krawędzi tworzących pełny cykl
std::vector<std::vector<int>> BnBLittle::findRemainingPaths(int no_of_cities, const std::vector<bool>& row_excluded, const std::vector<bool>& col_excluded, std::vector<std::vector<int>> included_paths) {
    std::vector<std::vector<int>> remaining_paths;
    bool first_path_found = false;
    bool second_path_found = false;
    std::vector<int> path1(2); std::vector<int> path2(2);

    for(int i = 0; i < no_of_cities; i++) {
        for(int j = 0; j < no_of_cities; j++) {
            if(!row_excluded[i] && !col_excluded[j]) {
                if(!makesSubTour(i, j, included_paths, first_path_found)) { //sprawdzenie czy połączenie nie tworzy podcyklu
                    if(!first_path_found) { //jeśli nie znaleziono pierwszej ze ścieżek, wykonaj tą czynność
                        path1[0] = i; path1[1] = j;
                        remaining_paths.push_back(path1);
                        included_paths.push_back(path1);
                        first_path_found = true;
                    } else { //jeśli znaleziono, to wykonaj tą - różnica to jedynie dodawanie wartości do innej tablicy
                        path2[0] = i; path2[1] = j;
                        remaining_paths.push_back(path2);
                        included_paths.push_back(path2);
                        second_path_found = true;
                    }
                }
            }
            if(second_path_found) break;
        }
        if(second_path_found) break;
    }

    return remaining_paths;
}

//rozpoczęcie algorytmu
bool BnBLittle::findTourLittle(const Graph& graph, int timeout_ms, bool print_result) {
    //inicjowanie stopera
    Timer timer;
    timer.start();

    //Stworzenie oryginalnej macierzy kosztów (kopia macierzy grafu)
    std::vector<std::vector<int>> cost_matrix(graph.no_of_cities, std::vector<int>(graph.no_of_cities));

    for(int i = 0; i < graph.no_of_cities; i++) {
        for(int j = 0; j < graph.no_of_cities; j++) {
            cost_matrix[i][j] = graph.cost_matrix[i][j];
        }
    }

    //stworzenie kolejki priorytetowej węzłów - na górze węzeł z najniższym dolnym ograniczeniem (lower bound)
    std::priority_queue<Node, std::vector<Node>, CompareNodes> unexplored_nodes;
    std::vector<std::vector<int>> final_paths; //wektor z ostatecznymi ścieżkami pomiędzy miastami
    int best_result = INT_MAX; //najlepsze do tej pory rozwiązanie

    //stworzenie zbioru X ze wszystkimi możliwymi połączeniami miast
    Node X(graph.no_of_cities);
    X.cost_matrix = cost_matrix;
    int reduction_sum = reduceCostMatrix(X.cost_matrix, graph.no_of_cities, X.row_excluded, X.col_excluded); //redukcja macierzy kosztów
    X.lower_bound = reduction_sum;
    X.side_length = graph.no_of_cities;

    unexplored_nodes.push(X);

    //wyciąganie kolejnych węzłów drzewa do momentu aż nie zostanie napotkany węzeł z większym dolnym ograniczeniem
    //od najlepszego wyniku
    while(true) {
        timer.stop();
        if(timeout_ms > 0 && timer.getTime() > timeout_ms) { //sprawdzenie, czy przekroczono limit czasu (jeśli ustawiony)
            if(print_result) {
                cout << "Przekroczono limit czasu - przerwanie dzialania\n";
            }
            return false;
        }

        Node next_node = unexplored_nodes.top();
        unexplored_nodes.pop();

        if(next_node.lower_bound >= best_result) break; //koniec pętli, jeśli w kolejce brak węzłów o niższym dolnym ograniczeniu niż najlepszy wynik

        std::vector<Node> sub_trees = createSubTrees(next_node, graph.no_of_cities);

        unexplored_nodes.push(sub_trees[0]);
        if(sub_trees[1].side_length == 2) { //jeśli macierz poddrzewa jest 2x2, to znajduje pozostałe trasy

            std::vector<std::vector<int>> remaining_paths = findRemainingPaths(graph.no_of_cities, sub_trees[1].row_excluded, sub_trees[1].col_excluded, sub_trees[1].included_paths);

            sub_trees[1].included_paths.push_back(remaining_paths[0]);
            sub_trees[1].included_paths.push_back(remaining_paths[1]);

            sub_trees[1].lower_bound = sub_trees[1].lower_bound +
                                       sub_trees[1].cost_matrix[remaining_paths[0][0]][remaining_paths[0][1]] +
                                       sub_trees[1].cost_matrix[remaining_paths[1][0]][remaining_paths[1][1]];

            if(sub_trees[1].lower_bound < best_result) {
                best_result = sub_trees[1].lower_bound;
                final_paths = sub_trees[1].included_paths;
            }

        } else {
            unexplored_nodes.push(sub_trees[1]);
        }
    }

    if(print_result) {
        printTour(final_paths, best_result, graph.no_of_cities);
    }

    return true;
}

//wyświetlenie wyniku
void BnBLittle::printTour(std::vector<std::vector<int>> paths, int result, int no_of_cities) {
    std::cout << "Najlepszy dystans: " << result << "\n";
    std::vector<int> path = paths[0];
    std::cout << "Przebyta trasa: " << path[0] << " -> " << path[1];
    int printed_paths = 1;

    while(printed_paths != no_of_cities) {
        for (int i = 1; i < no_of_cities; i++) {
            if(paths[i][0] == path[1]) {
                std::cout << " -> " << paths[i][1];
                printed_paths++;
                path = paths[i];
                break;
            }
        }
    }

    std::cout << "\n";
}
