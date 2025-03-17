#include <iostream>
#include <iomanip>
#include "SortingEngine.h"
#include "Sorter.h"
#include "ArrayManager.h"
#include "FileManager.h"

template <typename T>
SortingEngine<T>::SortingEngine(Sorter<T> sorter, ArrayManager<T> am, ArrayTester<T> tester, FileManager<T> fm)
    : sorter(sorter), am(am), tester(tester), fm(fm) {}

//masowe sortowanie tablic losowych przez wstawianie
template <typename T>
void SortingEngine<T>::massinsertsort(int size, int amount, bool display) {

    double timemean; //zmienna średniej czasu
    int errors = 0; //licznik błędów
    T* array;

    string filepath = getresultpath(); //wybranie nazwy pliku z wynikami pomiarów czasu
    if(filepath == ""){
        return;
    }

    for(int i = 1; i <= amount; ++i){

        array = am.genRandArr(size); //generowanie losowej tablicy

        if(display){ //wyświetlenie tablicy przed sortowaniem, gdy wybrana opcja
            cout << "LOSOWA TABLICA " << i << ":\n";
            am.displayArray(size, array);
        }

        //wykonanie sortowania i pomiar czasu
        timer.start();
        sorter.insertsort(size, array);
        timer.stop();

        if(display){
            cout << "POSORTOWANA TABLICA " << i << ":\n";
            am.displayArray(size, array);
        } else{ //gdy nie wybrano opcji wyświetlania tablicy, wyświetl informację o posortowaniu
            cout << "Posortowano tablice " << i << "\n";
        }

        if(!tester.issortcorrect(array, size)) errors++; //zwiększ licznik błędów, gdy wykryto błąd

        timemean += timer.getTime();

        fm.saveTimes(timer.getTime(), i, filepath); //zapisz wynik pomiaru do pliku

        delete[] array; //usuń tablicę z pamięci
    }

    timemean /= (1.0*amount); //wylicz średnią czasu
    cout<<fixed<<showpoint<<setprecision(5); //ustaw precyzję dla 5 miejsc po przecinku
    cout<<"Sredni czas: "<<timemean<<" ms\n";
    cout<<"Liczba bledow: "<<errors<<endl;
}

template <typename T>
void SortingEngine<T>::massshellsort1(int size, int amount, bool display) {

    double timemean = 0;
    int errors = 0;
    T* array;

    string filepath = getresultpath();
    if(filepath == ""){
        return;
    }

    for(int i = 1; i <= amount; ++i){

        array = am.genRandArr(size);

        if(display){
            cout << "LOSOWA TABLICA " << i << ":\n";
            am.displayArray(size, array);
        }

        timer.start();
        sorter.shellsort1(size, array);
        timer.stop();

        if(display){
            cout << "POSORTOWANA TABLICA " << i << ":\n";
            am.displayArray(size, array);
        } else{
            cout << "Posortowano tablice " << i << "\n";
        }

        if(!tester.issortcorrect(array, size)) errors++;

        timemean += timer.getTime();

        fm.saveTimes(timer.getTime(), i, filepath);

        delete[] array;
    }

    timemean /= (1.0*amount);
    cout<<fixed<<showpoint<<setprecision(5);
    cout<<"Sredni czas: "<<timemean<<" ms\n";
    cout<<"Liczba bledow: "<<errors<<endl;
}

template <typename T>
void SortingEngine<T>::massshellsort2(int size, int amount, bool display) {

    double timemean = 0;
    int errors = 0;
    T* array;

    string filepath = getresultpath();
    if(filepath == ""){
        return;
    }

    for(int i = 1; i <= amount; ++i){

        array = am.genRandArr(size);

        if(display){
            cout << "LOSOWA TABLICA " << i << ":\n";
            am.displayArray(size, array);
        }

        timer.start();
        sorter.shellsort2(size, array);
        timer.stop();

        if(display){
            cout << "POSORTOWANA TABLICA " << i << ":\n";
            am.displayArray(size, array);
        } else{
            cout << "Posortowano tablice " << i << "\n";
        }

        if(!tester.issortcorrect(array, size)) errors++;

        timemean += timer.getTime();

        fm.saveTimes(timer.getTime(), i, filepath);

        delete[] array;
    }

    timemean /= (1.0*amount);
    cout<<fixed<<showpoint<<setprecision(5);
    cout<<"Sredni czas: "<<timemean<<" ms\n";
    cout<<"Liczba bledow: "<<errors<<endl;
}

template <typename T>
void SortingEngine<T>::massquicksort(int size, int pchoice, int amount, bool display) {

    double timemean = 0;
    int errors = 0;
    T* array;

    string filepath = getresultpath();
    if(filepath == ""){
        return;
    }

    for(int i = 1; i <= amount; ++i){

        array = am.genRandArr(size);

        if(display){
            cout << "LOSOWA TABLICA " << i << ":\n";
            am.displayArray(size, array);
        }

        timer.start();
        sorter.quicksort(0, size-1, array, pchoice);
        timer.stop();

        if(display){
            cout << "POSORTOWANA TABLICA " << i << ":\n";
            am.displayArray(size, array);
        } else{
            cout << "Posortowano tablice " << i << "\n";
        }

        if(!tester.issortcorrect(array, size)) errors++;

        timemean += timer.getTime();

        fm.saveTimes(timer.getTime(), i, filepath);

        delete[] array;
    }

    timemean /= (1.0*amount);
    cout<<fixed<<showpoint<<setprecision(5);
    cout<<"Sredni czas: "<<timemean<<" ms\n";
    cout<<"Liczba bledow: "<<errors<<endl;
}

template <typename T>
void SortingEngine<T>::massheapsort(int size, int amount, bool display) {

    double timemean = 0;
    int errors = 0;
    T* array;

    string filepath = getresultpath();
    if(filepath == ""){
        return;
    }

    for(int i = 1; i <= amount; ++i){

        array = am.genRandArr(size);

        if(display){
            cout << "LOSOWA TABLICA " << i << ":\n";
            am.displayArray(size, array);
        }

        timer.start();
        sorter.heapsort(size, array);
        timer.stop();

        if(display){
            cout << "POSORTOWANA TABLICA " << i << ":\n";
            am.displayArray(size, array);
        } else{
            cout << "Posortowano tablice " << i << "\n";
        }

        if(!tester.issortcorrect(array, size)) errors++;

        timemean += timer.getTime();

        fm.saveTimes(timer.getTime(), i, filepath);

        delete[] array;
    }

    timemean /= (1.0*amount);
    cout<<fixed<<showpoint<<setprecision(5);
    cout<<"Sredni czas: "<<timemean<<" ms\n";
    cout<<"Liczba bledow: "<<errors<<endl;
}

//sortowanie przez wstawianie tablicy z pliku
template <typename T>
void SortingEngine<T>::fileinsertsort(std::string filepath, int amount, bool display) {

    int size;
    size = fm.getArrSize(filepath); //wyczytaj rozmiar tablicy
    if(size == 0) return; //koniec działania funkcji, gdy nie znaleziono pliku

    string filepath2 = getresultpath(); //wybierz nazwę pliku do zapisu pomiarów czasu
    if(filepath2 == ""){
        return;
    }

    double timemean = 0;
    int errors = 0;

    for(int i = 1; i <= amount; ++i) {
        T* array;
        array = fm.readArray(filepath);
        if(array == nullptr) return; //koniec działania funkcji, gdy nie znaleziono pliku

        if(display) {
            am.displayArray(size, array);
        }

        timer.start();
        sorter.insertsort(size, array);
        timer.stop();

        if(display) {
            am.displayArray(size, array);
        }else{
            cout << "Posortowano tablice " << i <<". raz\n";
        }

        if(!tester.issortcorrect(array, size)) errors++;

        timemean += timer.getTime();

        fm.saveTimes(timer.getTime(), i, filepath2);

        delete[] array;
    }

    timemean /= (1.0*amount);
    cout<<fixed<<showpoint<<setprecision(5);
    cout<<"Sredni czas: "<<timemean<<" ms\n";
    cout<<"Liczba bledow: "<<errors<<endl;
}

template <typename T>
void SortingEngine<T>::fileshellsort1(std::string filepath, int amount, bool display) {
    int size;
    size = fm.getArrSize(filepath);
    if(size == 0) return;

    string filepath2 = getresultpath();
    if(filepath2 == ""){
        return;
    }

    double timemean = 0;
    int errors = 0;

    for(int i = 1; i <= amount; ++i) {
        T* array;
        array = fm.readArray(filepath);
        if(array == nullptr) return;

        if(display) {
            am.displayArray(size, array);
        }

        timer.start();
        sorter.shellsort1(size, array);
        timer.stop();

        if(display) {
            am.displayArray(size, array);
        }else{
            cout << "Posortowano tablice " << i <<". raz\n";
        }

        if(!tester.issortcorrect(array, size)) errors++;

        timemean += timer.getTime();

        fm.saveTimes(timer.getTime(), i, filepath2);

        delete[] array;
    }

    timemean /= (1.0*amount);
    cout<<fixed<<showpoint<<setprecision(5);
    cout<<"Sredni czas: "<<timemean<<" ms\n";
    cout<<"Liczba bledow: "<<errors<<endl;
}

template <typename T>
void SortingEngine<T>::fileshellsort2(std::string filepath, int amount, bool display) {
    int size;
    size = fm.getArrSize(filepath);
    if(size == 0) return;

    string filepath2 = getresultpath();
    if(filepath2 == ""){
        return;
    }

    double timemean = 0;
    int errors = 0;

    for(int i = 1; i <= amount; ++i) {
        T* array;
        array = fm.readArray(filepath);
        if(array == nullptr) return;

        if(display) {
            am.displayArray(size, array);
        }

        timer.start();
        sorter.shellsort2(size, array);
        timer.stop();

        if(display) {
            am.displayArray(size, array);
        }else{
            cout << "Posortowano tablice " << i <<". raz\n";
        }

        if(!tester.issortcorrect(array, size)) errors++;

        timemean += timer.getTime();

        fm.saveTimes(timer.getTime(), i, filepath2);

        delete[] array;
    }

    timemean /= (1.0*amount);
    cout<<fixed<<showpoint<<setprecision(5);
    cout<<"Sredni czas: "<<timemean<<" ms\n";
    cout<<"Liczba bledow: "<<errors<<endl;
}

template <typename T>
void SortingEngine<T>::filequicksort(std::string filepath, int pchoice, int amount, bool display) {
    int size;
    size = fm.getArrSize(filepath);
    if(size == 0) return;

    string filepath2 = getresultpath();
    if(filepath2 == ""){
        return;
    }

    double timemean = 0;
    int errors = 0;

    for(int i = 1; i <= amount; ++i) {
        T* array;
        array = fm.readArray(filepath);
        if(array == nullptr) return;

        if(display) {
            am.displayArray(size, array);
        }

        timer.start();
        sorter.quicksort(0, size-1, array, pchoice);
        timer.stop();

        if(display) {
            am.displayArray(size, array);
        }else{
            cout << "Posortowano tablice " << i <<". raz\n";
        }

        if(!tester.issortcorrect(array, size)) errors++;

        timemean += timer.getTime();

        fm.saveTimes(timer.getTime(), i, filepath2);

        delete[] array;
    }

    timemean /= (1.0*amount);
    cout<<fixed<<showpoint<<setprecision(5);
    cout<<"Sredni czas: "<<timemean<<" ms\n";
    cout<<"Liczba bledow: "<<errors<<endl;
}

template <typename T>
void SortingEngine<T>::fileheapsort(std::string filepath, int amount, bool display) {
    int size;
    size = fm.getArrSize(filepath);
    if(size == 0) return;

    string filepath2 = getresultpath();

    double timemean = 0;
    int errors = 0;

    for(int i = 1; i <= amount; ++i) {
        T* array;
        array = fm.readArray(filepath);
        if(array == nullptr) return;

        if(display) {
            am.displayArray(size, array);
        }

        timer.start();
        sorter.heapsort(size, array);
        timer.stop();

        if(display) {
            am.displayArray(size, array);
        }else{
            cout << "Posortowano tablice " << i <<". raz\n";
        }

        if(!tester.issortcorrect(array, size)) errors++;

        timemean += timer.getTime();

        fm.saveTimes(timer.getTime(), i, filepath2);

        delete[] array;
    }

    timemean /= (1.0*amount);
    cout<<fixed<<showpoint<<setprecision(5);
    cout<<"Sredni czas: "<<timemean<<" ms\n";
    cout<<"Liczba bledow: "<<errors<<endl;
}

template <typename T>
string SortingEngine<T>::getresultpath(){
    std::string resfilepath;
    std::cout<<"Wybierz nazwe/sciezke dla pliku do zapisu wynikow czasu:"<<std::endl;
    std::cin>>resfilepath;

    return resfilepath+".csv";
}

template class SortingEngine<int>;
template class SortingEngine<float>;
