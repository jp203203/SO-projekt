#ifndef UNTITLED_SORTINGENGINE_H
#define UNTITLED_SORTINGENGINE_H

#include "Sorter.h"
#include "ArrayManager.h"
#include "Timer.h"
#include "ArrayTester.h"
#include "FileManager.h"


class SortingEngine {
public:
    SortingEngine(Sorter sorter, ArrayManager am, ArrayTester tester, FileManager fm);

    void massinsertsort(int size, int amount);
    void massshellsort1(int size, int amount);
    void massshellsort2(int size, int amount);
    void massquicksort(int size, int pchoice, int amount);
    void massheapsort(int size, int amount);

    void fileinsertsort(string filepath, int amount);
    void fileshellsort1(string filepathn, int amount);
    void fileshellsort2(string filepath, int amount);
    void filequicksort(string filepath, int pchoice, int amount);
    void fileheapsort(string filepath, int amount);

private:
    ArrayManager am;
    Sorter sorter;
    Timer timer;
    ArrayTester tester;
    FileManager fm;

    string getresultpath();
};


#endif //UNTITLED_SORTINGENGINE_H
