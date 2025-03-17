#include <iostream>
#include "SortingEngine.h"
#include "Sorter.h"
#include "ArrayManager.h"
#include "FileManager.h"

SortingEngine::SortingEngine(Sorter sorter, ArrayManager am, ArrayTester tester, FileManager fm)
    : sorter(sorter), am(am), tester(tester), fm(fm) {}

void SortingEngine::massinsertsort(int size, int amount) {

    double timemean;
    int errors = 0;
    int* array;

    string filepath = getresultpath();
    if(filepath == ""){
        return;
    }

    for(int i = 1; i <= amount; ++i){

        array = am.genRandArr(size);
        cout<<"LOSOWA TABLICA "<<i<<":\n";
        am.displayArray(size, array);

        timer.start();
        sorter.insertsort(size, array);
        timer.stop();

        cout<<"POSORTOWANA TABLICA "<<i<<":\n";
        am.displayArray(size, array);

        if(!tester.issortcorrect(array, size)) errors++;

        timemean += timer.getTime();

        fm.saveTimes(timer.getTime(), i, filepath);

        delete[] array;
    }

    timemean /= (1.0*amount);

    cout<<"Sredni czas: "<<timemean<<" ms\n";
    cout<<"Liczba bledow: "<<errors<<endl;
}

void SortingEngine::massshellsort1(int size, int amount) {

    double timemean = 0;
    int errors = 0;
    int* array;

    string filepath = getresultpath();
    if(filepath == ""){
        return;
    }

    for(int i = 1; i <= amount; ++i){

        array = am.genRandArr(size);
        cout<<"LOSOWA TABLICA "<<i<<":\n";
        am.displayArray(size, array);

        timer.start();
        sorter.shellsort1(size, array);
        timer.stop();

        cout<<"POSORTOWANA TABLICA "<<i<<":\n";
        am.displayArray(size, array);

        if(!tester.issortcorrect(array, size)) errors++;

        timemean += timer.getTime();

        fm.saveTimes(timer.getTime(), i, filepath);

        delete[] array;
    }

    timemean /= (1.0*amount);
    cout<<"Sredni czas: "<<timemean<<" ms\n";
    cout<<"Liczba bledow: "<<errors<<endl;
}

void SortingEngine::massshellsort2(int size, int amount) {

    double timemean = 0;
    int errors = 0;
    int* array;

    string filepath = getresultpath();
    if(filepath == ""){
        return;
    }

    for(int i = 1; i <= amount; ++i){

        array = am.genRandArr(size);
        cout<<"LOSOWA TABLICA "<<i<<":\n";
        am.displayArray(size, array);

        timer.start();
        sorter.shellsort2(size, array);
        timer.stop();

        cout<<"POSORTOWANA TABLICA "<<i<<":\n";
        am.displayArray(size, array);

        if(!tester.issortcorrect(array, size)) errors++;

        timemean += timer.getTime();

        fm.saveTimes(timer.getTime(), i, filepath);

        delete[] array;
    }

    timemean /= (1.0*amount);
    cout<<"Sredni czas: "<<timemean<<" ms\n";
    cout<<"Liczba bledow: "<<errors<<endl;
}

void SortingEngine::massquicksort(int size, int pchoice, int amount) {

    double timemean = 0;
    int errors = 0;
    int* array;

    string filepath = getresultpath();
    if(filepath == ""){
        return;
    }

    for(int i = 1; i <= amount; ++i){

        array = am.genRandArr(size);
        cout<<"LOSOWA TABLICA "<<i<<":\n";
        am.displayArray(size, array);

        timer.start();
        sorter.quicksort(0, size-1, array, pchoice);
        timer.stop();

        cout<<"POSORTOWANA TABLICA "<<i<<":\n";
        am.displayArray(size, array);

        if(!tester.issortcorrect(array, size)) errors++;

        timemean += timer.getTime();

        fm.saveTimes(timer.getTime(), i, filepath);

        delete[] array;
    }

    timemean /= (1.0*amount);
    cout<<"Sredni czas: "<<timemean<<" ms\n";
    cout<<"Liczba bledow: "<<errors<<endl;
}

void SortingEngine::massheapsort(int size, int amount) {

    double timemean = 0;
    int errors = 0;
    int* array;

    string filepath = getresultpath();
    if(filepath == ""){
        return;
    }

    for(int i = 1; i <= amount; ++i){

        array = am.genRandArr(size);
        cout<<"LOSOWA TABLICA "<<i<<":\n";
        am.displayArray(size, array);

        timer.start();
        sorter.heapsort(size, array);
        timer.stop();

        cout<<"POSORTOWANA TABLICA "<<i<<":\n";
        am.displayArray(size, array);

        if(!tester.issortcorrect(array, size)) errors++;

        timemean += timer.getTime();

        fm.saveTimes(timer.getTime(), i, filepath);

        delete[] array;
    }

    timemean /= (1.0*amount);
    cout<<"Sredni czas: "<<timemean<<" ms\n";
    cout<<"Liczba bledow: "<<errors<<endl;
}

void SortingEngine::fileinsertsort(std::string filepath, int amount) {
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
        int* array;
        array = fm.readArray(filepath);
        if(array == nullptr) return;

        am.displayArray(size, array);

        timer.start();
        sorter.insertsort(size, array);
        timer.stop();

        am.displayArray(size, array);

        if(!tester.issortcorrect(array, size)) errors++;

        timemean += timer.getTime();

        fm.saveTimes(timer.getTime(), i, filepath2);

        delete[] array;
    }

    timemean /= (1.0*amount);
    cout<<"Sredni czas: "<<timemean<<" ms\n";
    cout<<"Liczba bledow: "<<errors<<endl;
}

void SortingEngine::fileshellsort1(std::string filepath, int amount) {
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
        int* array;
        array = fm.readArray(filepath);
        if(array == nullptr) return;

        am.displayArray(size, array);

        timer.start();
        sorter.shellsort1(size, array);
        timer.stop();

        am.displayArray(size, array);

        if(!tester.issortcorrect(array, size)) errors++;

        timemean += timer.getTime();

        fm.saveTimes(timer.getTime(), i, filepath2);

        delete[] array;
    }

    timemean /= (1.0*amount);
    cout<<"Sredni czas: "<<timemean<<" ms\n";
    cout<<"Liczba bledow: "<<errors<<endl;
}

void SortingEngine::fileshellsort2(std::string filepath, int amount) {
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
        int* array;
        array = fm.readArray(filepath);
        if(array == nullptr) return;

        am.displayArray(size, array);

        timer.start();
        sorter.shellsort2(size, array);
        timer.stop();

        am.displayArray(size, array);

        if(!tester.issortcorrect(array, size)) errors++;

        timemean += timer.getTime();

        fm.saveTimes(timer.getTime(), i, filepath2);

        delete[] array;
    }

    timemean /= (1.0*amount);
    cout<<"Sredni czas: "<<timemean<<" ms\n";
    cout<<"Liczba bledow: "<<errors<<endl;
}

void SortingEngine::filequicksort(std::string filepath, int pchoice, int amount) {
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
        int* array;
        array = fm.readArray(filepath);
        if(array == nullptr) return;

        am.displayArray(size, array);

        timer.start();
        sorter.quicksort(0, size-1, array, pchoice);
        timer.stop();

        am.displayArray(size, array);

        if(!tester.issortcorrect(array, size)) errors++;

        timemean += timer.getTime();

        fm.saveTimes(timer.getTime(), i, filepath2);

        delete[] array;
    }

    timemean /= (1.0*amount);
    cout<<"Sredni czas: "<<timemean<<" ms\n";
    cout<<"Liczba bledow: "<<errors<<endl;
}

void SortingEngine::fileheapsort(std::string filepath, int amount) {
    int size;
    size = fm.getArrSize(filepath);
    if(size == 0) return;

    string filepath2 = getresultpath();

    double timemean = 0;
    int errors = 0;

    for(int i = 1; i <= amount; ++i) {
        int* array;
        array = fm.readArray(filepath);
        if(array == nullptr) return;

        am.displayArray(size, array);

        timer.start();
        sorter.heapsort(size, array);
        timer.stop();

        am.displayArray(size, array);

        if(!tester.issortcorrect(array, size)) errors++;

        timemean += timer.getTime();

        fm.saveTimes(timer.getTime(), i, filepath2);

        delete[] array;
    }

    timemean /= (1.0*amount);
    cout<<"Sredni czas: "<<timemean<<" ms\n";
    cout<<"Liczba bledow: "<<errors<<endl;
}

string SortingEngine::getresultpath(){
    std::string resfilepath;
    std::cout<<"Wybierz nazwe/sciezke dla pliku do zapisu wynikow czasu:"<<std::endl;
    std::cin>>resfilepath;

    return resfilepath+".csv";
}
