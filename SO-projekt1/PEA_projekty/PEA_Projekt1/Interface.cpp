#include "Interface.h"
#include <iostream>
#include <iomanip>
#include <future>

using namespace std;

Interface::Interface(FileManager fm, GraphGenerator gg, BruteForce bf, BnBLittle bnbl, Timer timer, Dynamic d)
{
    file_manager = fm;
    brute_force = bf;
    generator = gg;
    little = bnbl;
    dynamic = d;
    this -> timer = timer;
}

void Interface::welcomeScreen() {
    while(true) {
        system("cls");
        cout<<"1. Wczytaj graf\n"
            <<"2. Wygeneruj graf\n"
            <<"3. Przeprowadz testy wielokrotnie na losowych instancjach\n"
            <<"4. Zakoncz program\n";

        int option = optionInput(4);

        switch(option) {
            case 1: {
                Graph graph = file_manager.loadGraph();
                graphOptionsInterface(false, graph);
                break;
            }
            case 2: {
                int no_of_cities;
                cout << "Podaj ilosc miast do zwiedzenia:\n";
                no_of_cities = optionInput(0, 2);
                Graph graph = generator.generateGraph(no_of_cities);
                graphOptionsInterface(true, graph);
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

void Interface::graphOptionsInterface(bool save_button, const Graph &graph) {
    int limit;
    while(true) {
        system("cls");
        graph.displayGraph();

        limit = save_button ? 3 : 2;
        cout << "Co zrobic z grafem?\n"
             << "1. Znajdz najkrotsza trase\n"
             << "2. Powrot (usuwa graf)\n";
        if(save_button) {
            cout << "3. Zapisz graf\n";
        }

        int option = optionInput(limit);
        switch(option) {
            case 1:
                runOneOptions(graph);
                break;
            case 2:
                return;
            case 3:
                file_manager.saveGraph(graph);
                save_button = false;
                break;
        }
    }
}

void Interface::runOneOptions(const Graph& graph) {
    while(true) {
        cout << "Wybierz metode:\n"
             << "1. Algorytm brute force\n"
             << "2. Algorytm Little'a (Branch & Bound)\n"
             << "3. Programowanie dynamiczne\n"
             << "4. Wszystkie metody naraz (nie mierzy czasu)\n"
             << "5. Powrot\n";

        int option = optionInput(5);
        double time;
        switch(option) {
            case 1:
                timer.start();
                brute_force.findTourBF(graph);
                timer.stop();
                time = timer.getTime();

                cout << fixed << showpoint << setprecision(5);
                cout << "Czas dzialania algorytmu: " << time << " ms\n\n";
                break;
            case 2:
                timer.start();
                little.findTourLittle(graph);
                timer.stop();
                time = timer.getTime();

                cout << fixed << showpoint << setprecision(5);
                cout << "Czas dzialania algorytmu: " << time << " ms\n\n";
                break;
            case 3:
                timer.start();
                dynamic.findTourDynamic(graph);
                timer.stop();
                time = timer.getTime();

                cout << fixed << showpoint << setprecision(5);
                cout << "Czas dzialania algorytmu: " << time << " ms\n\n";
                break;
            case 4:
                brute_force.findTourBF(graph);
                little.findTourLittle(graph);
                dynamic.findTourDynamic(graph);
                break;
            case 5:
                return;
        }
    }
}

void Interface::runMultipleOptions() {
    system("cls");
    cout << "Podaj ilosc rozpatrywanych miast:\n";
    int no_of_cities = optionInput(0, 2);

    while(true) {
        cout << "\nWybierz metode:\n"
             << "1. Algorytm brute force\n"
             << "2. Algorytm Little'a\n"
             << "3. Programowanie dynamiczne\n"
             << "4. Powrot\n";

        int option = optionInput(4);

        if(option == 4) return;

        cout << "Wybierz ilosc powtorzen:\n";
        int repetitions = optionInput(0);

        double avg_time = 0;
        int time_limit = 0;
        int interruptions = 0;

        if(option == 2) { //jeżeli algorytm BnB to również sprawdza przekroczenie czasu wykonywania
            cout << "Wybierz limit czasu (w ms): \n";
            time_limit = optionInput(0);
        }

        for(int i = 0; i < repetitions; i++) {
            Graph graph = generator.generateGraph(no_of_cities);
            switch(option) {
                case 1:
                    timer.start();
                    brute_force.findTourBF(graph, false);
                    timer.stop();
                    avg_time += timer.getTime();
                    break;
                case 2: {
                    timer.start();
                    bool success = little.findTourLittle(graph, time_limit, false);
                    timer.stop();
                    if(success) {
                        avg_time += timer.getTime();
                    } else {
                        interruptions++;
                    }
                    break;
                }
                case 3:
                    timer.start();
                    dynamic.findTourDynamic(graph, false);
                    timer.stop();
                    avg_time += timer.getTime();
                    break;
            }
            cout << "Wykonano " << i + 1 << ". powtorzenie\n";
        }
        if(option == 2) {
            cout << fixed << showpoint << setprecision(1);
            cout << "Ilosc przerwanych wywolan: " << interruptions << " (" << ((interruptions * 1.0) / repetitions * 100) <<"%)\n";
            repetitions -= interruptions;
        }
        avg_time /= repetitions;
        cout << fixed << showpoint << setprecision(5);
        cout << "Przecietny czas dzialania algorytmu: " << avg_time << " ms\n";
    }
}

int Interface::optionInput(int limit, int lower_limit) {
    int option;

    while(!(cin>>option) || (option > limit && limit != 0) || option < lower_limit) {
        cout << "Niepoprawna opcja! Wpisz inna wartosc:\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return option;
}