#ifndef AIZO_PROJEKT_FILEMANAGER_H
#define AIZO_PROJEKT_FILEMANAGER_H

#include <fstream>
#include <iostream>
#include <string>
#include "ArrayManager.h"

template <typename T>
class FileManager{
public:
    explicit FileManager();

    void saveArray (T* array, int size); ///zapisanie tablicy do pliku tekstowego

    T* readArray (std::string filepath); ///wczytanie tablicy z pliku tekstowego

    int getArrSize (std::string filepath); ///zwraca ilość elementów tablicy z pliku tekstowego

    void saveTimes (double time, int index, std::string filepath); ///zapisuje pomiar czasu do pliku .csv
};

#endif //AIZO_PROJEKT_FILEMANAGER_H
