#ifndef UNTITLED_FILEMANAGER_H
#define UNTITLED_FILEMANAGER_H

#include <fstream>
#include <iostream>
#include <string>
#include "ArrayManager.h"

class FileManager{
public:
    explicit FileManager(ArrayManager arrayManager);

    void saveArray (int* array, int size, bool isSorted); ///zapisanie tablicy do pliku tekstowego

    int* readArray (std::string filepath); ///wczytanie tablicy z pliku tekstowego

    int getArrSize (std::string filepath); ///zwraca ilość elementów tablicy z pliku tekstowego

    void saveTimes (double time, int index, std::string filepath); ///zapisuje pomiar czasu do pliku .csv
};

#endif //UNTITLED_FILEMANAGER_H
