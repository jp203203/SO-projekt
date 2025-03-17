#ifndef AIZO_PROJEKT_SORTINGENGINE_H
#define AIZO_PROJEKT_SORTINGENGINE_H

#include "Sorter.h"
#include "ArrayManager.h"
#include "Timer.h"
#include "ArrayTester.h"
#include "FileManager.h"

template <typename T>
class SortingEngine {
public:
    SortingEngine(Sorter<T> sorter, ArrayManager<T> am, ArrayTester<T> tester, FileManager<T> fm);

    //masowe sortowanie tablic losowych
    void massinsertsort(int size, int amount, bool display); ///masowe sortowanie przez wstawianie
    void massshellsort1(int size, int amount, bool display); ///masowe sortowanie Shella - sekwencja Shella
    void massshellsort2(int size, int amount, bool display); ///masowe sortowanie Shella - sekwencja Hibbarda
    void massquicksort(int size, int pchoice, int amount, bool display); ///masowe sortowanie szybkie
    void massheapsort(int size, int amount, bool display); ///masowe sortowanie stogowe

    //masowe sortowanie tablic wczytanych z pliku
    void fileinsertsort(string filepath, int amount, bool display); ///sortowanie z pliku przez wstawianie
    void fileshellsort1(string filepath, int amount, bool display); ///sortowanie z pliku Shella - sekwencja Shella
    void fileshellsort2(string filepath, int amount, bool display); ///sortowanie z pliku Shella - sekwencja Hibbarda
    void filequicksort(string filepath, int pchoice, int amount, bool display); ///sortowanie z pliku szybkie
    void fileheapsort(string filepath, int amount, bool display); ///sortowanie z pliku stogowe

private:
    ArrayManager<T> am;
    Sorter<T> sorter;
    Timer timer;
    ArrayTester<T> tester;
    FileManager<T> fm;

    string getresultpath();
};


#endif //AIZO_PROJEKT_SORTINGENGINE_H
