#include"Interface.h"
#include <iostream>
#include <limits>
#include <iomanip>

using namespace std;

Interface::Interface(FileManager fm, MST mst, ShortestPath sp, GraphGenerator gg, Timer timer)
{
    file_manager = fm;
    mst_algorithms = mst;
    sp_algorithms = sp;
    generator = gg;
    this -> timer = timer;
}

//ekran powitalny z opcjami wczytania i generowania grafów oraz przeprowadzenia testów
void Interface::welcomeScreen() {
    while(true) {
        system("cls");
        cout<<"1. Wczytaj graf\n"
            <<"2. Wygeneruj graf\n"
            <<"3. Przeprowadz testy wielokrotnie (losowe grafy)\n"
            <<"4. Zakoncz program\n";

        int option = optionInput(4);

        switch(option) {
            case 1: {
                auto [graph_list, graph_matrix] = file_manager.loadGraph();
                graphOptionsInterface(false, graph_list, graph_matrix); //false - graf zapisany więc nie wyświetla opcji zapisu
                break;
            }
            case 2: {
                int no_of_vertexes, density;
                cout << "Podaj ilosc wierzcholkow:\n";
                no_of_vertexes = optionInput(0);
                cout << "Podaj gestosc grafu (w procentach):\n";
                density = optionInput(100);
                auto [graph_list, graph_matrix] = generator.generateGraph(no_of_vertexes, density);
                graphOptionsInterface(true, graph_list, graph_matrix); //true - wyświetla opcje zapisu grafu
                break;
            }
            case 3:
                runMultipleOptions();
                break;
            case 4:
                return;
        }
    }
}

//ekran wyświetlany po wczytaniu/wygenerowaniu grafu
void Interface::graphOptionsInterface(bool save_button, const GraphList& graph_list, const GraphMatrix& graph_matrix) {
    int limit;
    while(true) {
        system("cls");
        graph_matrix.displayGraph();
        graph_list.displayGraph();

        limit = save_button ? 3 : 2;
        cout << "Co zrobic z grafem?\n"
             << "1. Wykonaj algorytm\n"
             << "2. Powrot (usuwa graf)\n";
        if (save_button) { //wyświetla opcje zapisu grafu, gdy save_button = true
            cout << "3. Zapisz graf\n";
        }

        int option = optionInput(limit);
        switch (option) {
            case 1:
                runOneOptions(graph_list, graph_matrix);
                break;
            case 2:
                return;
            case 3:
                file_manager.saveGraph(graph_matrix);
                save_button = false; //po zapisaniu grafu przestań wyświetlać opcje zapisu
                break;
        }
    }
}

//ekran z opcjami pojedynczego wywołania algorytmu
void Interface::runOneOptions(const GraphList& graph_list, const GraphMatrix& graph_matrix) {
    while(true) {
        cout<<"\nWybierz algorytm:\n"
            <<"1. Algorytm Dijkstry (najkrotsza sciezka)\n"
            <<"2. Algorytm Bellmana-Forda (najkrotsza sciezka)\n"
            <<"3. Algorytm Prima (MST)\n"
            <<"4. Algorytm Kruskala (MST)\n"
            <<"5. Powrot\n";

        int option = optionInput(5);
        double list_time, matrix_time;
        switch(option) {
            case 1: {   //w zależności od wybranej opcji odpala algorytmy, mierzy czasy
                int start, finish;
                cout<<"Podaj poczatek sciezki:\n";
                start = optionInput(graph_list.no_of_vertexes - 1, 0);
                cout<<"Podaj koniec sciezki:\n";
                finish = optionInput(graph_list.no_of_vertexes - 1, 0);

                timer.start();
                int** res_l = sp_algorithms.DijkstraList(graph_list, start);
                timer.stop();
                list_time = timer.getTime();

                timer.start();
                int** res_m = sp_algorithms.DijkstraMatrix(graph_matrix, start);
                timer.stop();
                matrix_time = timer.getTime();

                cout<<"\nWyniki dla macierzy:\n";
                sp_algorithms.SPResult(res_m, start, finish);
                cout<<fixed<<showpoint<<setprecision(5);
                cout<<"czas = "<<matrix_time<<" ms\n";

                cout<<"\nWyniki dla listy:\n";
                sp_algorithms.SPResult(res_l, start, finish);
                cout<<fixed<<showpoint<<setprecision(5);
                cout<<"czas = "<<list_time<<" ms\n";
                break;
            }
            case 2: {
                int start, finish;
                cout<<"Podaj poczatek sciezki:\n";
                start = optionInput(graph_list.no_of_vertexes - 1, 0);
                cout<<"Podaj koniec sciezki:\n";
                finish = optionInput(graph_list.no_of_vertexes - 1, 0);

                timer.start();
                int** res_l = sp_algorithms.BellmanFordList(graph_list, start);
                timer.stop();
                list_time = timer.getTime();

                timer.start();
                int** res_m = sp_algorithms.BellmanFordMatrix(graph_matrix, start);
                timer.stop();
                matrix_time = timer.getTime();

                cout<<"\nWyniki dla macierzy:\n";
                sp_algorithms.SPResult(res_m, start, finish);
                cout<<fixed<<showpoint<<setprecision(5);
                cout<<"czas = "<<matrix_time<<" ms\n";

                cout<<"\nWyniki dla listy:\n";
                sp_algorithms.SPResult(res_l, start, finish);
                cout<<fixed<<showpoint<<setprecision(5);
                cout<<"czas = "<<list_time<<" ms\n";
                break;
            }
            case 3: {
                timer.start();
                int **res_l = mst_algorithms.PrimList(graph_list, 0);
                timer.stop();
                list_time = timer.getTime();

                timer.start();
                int **res_m = mst_algorithms.PrimMatrix(graph_matrix, 0);
                timer.stop();
                matrix_time = timer.getTime();

                cout<<"\nWyniki dla macierzy:\n";
                mst_algorithms.PrimResult(res_m, graph_matrix.no_of_vertexes);
                cout<<fixed<<showpoint<<setprecision(5);
                cout<<"czas = "<<matrix_time<<" ms\n";

                cout<<"\nWyniki dla listy:\n";
                mst_algorithms.PrimResult(res_l, graph_list.no_of_vertexes);
                cout<<fixed<<showpoint<<setprecision(5);
                cout <<"czas = "<<list_time<<" ms\n";
                break;
            }
            case 4: {
                timer.start();
                GEdge::Edge *res_l = mst_algorithms.KruskalList(graph_list);
                timer.stop();
                list_time = timer.getTime();

                timer.start();
                GEdge::Edge *res_m = mst_algorithms.KruskalMatrix(graph_matrix);
                timer.stop();
                matrix_time = timer.getTime();

                cout<<"\nWyniki dla macierzy:\n";
                mst_algorithms.KruskalResult(res_m, graph_matrix.no_of_vertexes - 1);
                cout<<fixed<<showpoint<<setprecision(5);
                cout<<"czas = "<<matrix_time<<" ms\n";

                cout<<"\nWyniki dla listy:\n";
                mst_algorithms.KruskalResult(res_l, graph_list.no_of_vertexes - 1);
                cout<<fixed<<showpoint<<setprecision(5);
                cout<<"czas = "<<list_time<<" ms\n";
                break;
            }
            case 5:
                return;
        }
    }
}

//ekran z opcjami dla wywołania algorytmu wielokrotnie
void Interface::runMultipleOptions() {
    system("cls");
    cout<<"Podaj ilosc wierzcholkow grafow:\n";
    int no_of_vertexes = optionInput(0);
    cout<<"Podaj gestosc grafow:\n";
    int density = optionInput(100);

    while(true) {
        cout << "\nWybierz algorytm:\n"
             << "1. Algorytm Dijkstry (najkrotsza sciezka)\n"
             << "2. Algorytm Bellmana-Forda (najkrotsza sciezka)\n"
             << "3. Algorytm Prima (MST)\n"
             << "4. Algorytm Kruskala (MST)\n"
             << "5. Powrot\n";

        int option = optionInput(5);

        if (option == 5) return;

        cout << "Wybierz ilosc powtorzen:\n";
        int repetitions = optionInput(0);

        //średnie czasy, na początku sumuje a później dzieli przez ilość powtórzeń
        double average_time_list = 0;
        double average_time_matrix = 0;
        for (int i = 0; i < repetitions; i++) { //tak samo jak dla pojedynczych wywołań, ale robi to po kilka razy
            auto [graph_list, graph_matrix] = generator.generateGraph(no_of_vertexes, density);
            switch (option) {
                case 1:
                    timer.start();
                    sp_algorithms.DijkstraList(graph_list, 0);
                    timer.stop();
                    average_time_list += timer.getTime();

                    timer.start();
                    sp_algorithms.DijkstraMatrix(graph_matrix, 0);
                    timer.stop();
                    average_time_matrix += timer.getTime();

                    break;
                case 2:
                    timer.start();
                    sp_algorithms.BellmanFordList(graph_list, 0);
                    timer.stop();
                    average_time_list += timer.getTime();

                    timer.start();
                    sp_algorithms.BellmanFordMatrix(graph_matrix, 0);
                    timer.stop();
                    average_time_matrix += timer.getTime();

                    break;
                case 3:
                    timer.start();
                    mst_algorithms.PrimList(graph_list, 0);
                    timer.stop();
                    average_time_list += timer.getTime();

                    timer.start();
                    mst_algorithms.PrimMatrix(graph_matrix, 0);
                    timer.stop();
                    average_time_matrix += timer.getTime();

                    break;
                case 4:
                    timer.start();
                    mst_algorithms.KruskalList(graph_list);
                    timer.stop();
                    average_time_list += timer.getTime();

                    timer.start();
                    mst_algorithms.KruskalMatrix(graph_matrix);
                    timer.stop();
                    average_time_matrix += timer.getTime();

                    break;
            }

        }
        //oblicza i wyświetla średnie czasy
        average_time_list = average_time_list / repetitions;
        average_time_matrix = average_time_matrix / repetitions;

        cout<<fixed<<showpoint<<setprecision(5);
        cout<<"Przecietny czas dla listy: "<<average_time_list<<" ms\n";
        cout<<"Przecietny czas dla macierzy: "<<average_time_matrix<<" ms\n";
    }
}

//funkcja prosząca o podanie opcji
int Interface::optionInput(int limit, int lower_limit) {
    int option;
    //przyjmuje tylko dane typu int, gdy limit = 0 to brak górnego limitu
    //limit dolny domyślnie to 1, można podać inny
    while(!(cin>>option) || (option > limit && limit != 0) || option < lower_limit){
        cout<<"Niepoprawna opcja! Wpisz inna wartosc\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return option;
}