#include "Interface.h"
#include <iostream>
#include "FileManager.h"
#include "ArrayManager.h"
#include "Sorter.h"
#include "SortingEngine.h"

template <typename T>
Interface<T>::Interface() {}

//wyświetl interfejs
template <typename T>
void Interface<T>::displayinterface() {

    ArrayManager<T> am;
    FileManager<T> fm;
    Sorter<T> sorter;
    ArrayTester<T> tester;
    SortingEngine<T> sortengine(sorter, am, tester, fm);

    while(true){

        int option1;
        cout<<"Wybierz opcje:\n";
        cout<<"1. Wygeneruj tablice\n";
        cout<<"2. Sortuj\n";
        cout<<"3. Zakoncz program\n";

        option1 = optioninput(3);
        system("cls");

        switch(option1){
            case 1:

                int option2;
                T* array;
                int size;

                cout<<"Jaka tablice wygenerowac?\n";
                cout<<"1. Calkowicie losowa\n";
                cout<<"2. Posortowana\n";
                cout<<"3. Posortowana malejaco\n";

                option2 = optioninput(3);
                system("cls");

                cout<<"Podaj rozmiar tablicy:\n";
                size = optioninput(0);

                switch(option2){
                    case 1:
                        array = am.genRandArr(size);
                        break;
                    case 2:
                        int part;
                        cout<<"Podaj, jaka czesc tablicy (w procentach) ma byc posortowana:\n";
                        part = optioninput(100);
                        array = am.genRandArrPart(part, size);
                        break;
                    case 3:
                        array = am.genRandArr(size);
                        sorter.insertsortdesc(size, array);
                        break;
                }
                cout<<"Wygenerowana tablica:\n";
                am.displayArray(size, array);

                int saveoption;
                cout<<"Zapisac tablice? [1 - tak, 2 - nie]\n";
                saveoption = optioninput(2);

                if(saveoption==1){
                    fm.saveArray(array, size);
                }
                system("pause");
                delete[] array;
                system("cls");
                break;
            case 2:
                int option3;
                cout<<"1. Sortowanie tablicy wczytanej z pliku\n";
                cout<<"2. Sortowanie masowe losowych tablic\n";
                option3 = optioninput(2);
                system("cls");

                int sortoption;
                cout<<"Wybierz algorytm:\n";
                cout<<"1. Sortowanie przez wstawianie\n";
                cout<<"2. Sortowanie Shella - odstepy N/2^k\n";
                cout<<"3. Sortowanie Shella - odstepy 2^k - 1\n";
                cout<<"4. Sortowanie szybkie\n";
                cout<<"5. Sortowanie stogowe\n";
                sortoption = optioninput(5);

                int displayoption;
                bool display;
                cout<<"Wyswietlac tablice i wyniki sortowania? [1 - tak, 2 - nie]\n";
                displayoption = optioninput(2);

                if(displayoption == 1){
                    display = true;
                }else{
                    display = false;
                }

                switch(option3){
                    case 2:
                        cout<<"Podaj rozmiar tablicy:\n";
                        size = optioninput(0);

                        int amount;
                        cout<<"Podaj ilosc sortowanych tablic:\n";
                        amount = optioninput(0);

                        system("cls");
                        if(sortoption == 1) sortengine.massinsertsort(size, amount, display);
                        if(sortoption == 2) sortengine.massshellsort1(size, amount, display);
                        if(sortoption == 3) sortengine.massshellsort2(size, amount, display);
                        if(sortoption == 4){
                            int pchoice;
                            cout<<"Jaki pivot wybrac?\n";
                            cout<<"1. Lewy\n";
                            cout<<"2. Prawy\n";
                            cout<<"3. Srodkowy\n";
                            cout<<"4. Losowy\n";
                            pchoice = optioninput(4);

                            sortengine.massquicksort(size, pchoice, amount, display);
                        }
                        if(sortoption == 5) sortengine.massheapsort(size, amount, display);
                        break;
                    case 1:
                        string filepath;
                        cout<<"Podaj sciezke pliku: ";
                        cin>>filepath;

                        cout<<"Podaj ile razy tablica ma byc sortowana:\n";
                        amount = optioninput(0);

                        system("cls");
                        if(sortoption == 1)sortengine.fileinsertsort(filepath, amount, display);
                        if(sortoption == 2)sortengine.fileshellsort1(filepath, amount, display);
                        if(sortoption == 3)sortengine.fileshellsort2(filepath, amount, display);
                        if(sortoption == 4){
                            int pchoice;
                            cout<<"Jaki pivot wybrac?\n";
                            cout<<"1. Lewy\n";
                            cout<<"2. Prawy\n";
                            cout<<"3. Srodkowy\n";
                            cout<<"4. Losowy\n";
                            pchoice = optioninput(4);

                            sortengine.filequicksort(filepath, pchoice, amount, display);
                        }
                        if(sortoption == 5)sortengine.fileheapsort(filepath, amount, display);
                        break;
                }
                system("pause");
                system("cls");

                break;
            case 3:
                exit(0);
        }
    }
}

//wybierz opcję
template <typename T>
int Interface<T>::optioninput(int limit){
    int option;

    //pętla wykonuje się do momentu aż wybrana opcja będzie liczbą całkowitą, będzie większa od 0 i będzie mieściła się
    //w limicie - gdy do argumentu limit przekazane jest 0, to ten warunek jest ignorowany (nie ma limitu)
    while(!(cin>>option) || (option > limit && limit != 0) || option < 1){
        cout<<"Niepoprawna opcja! Wpisz inna wartosc\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return option;
}

template class Interface<int>;
template class Interface<float>;