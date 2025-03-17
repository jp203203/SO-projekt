#ifndef AIZO_PROJEKT_ARRAYMANAGER_H
#define AIZO_PROJEKT_ARRAYMANAGER_H

#include <cstdlib>
#include <ctime>

template <typename T>
class ArrayManager{
public:
    ArrayManager();

    T* genRandArr(int size); ///generowanie tablicy losowych wartości
    T* genRandArrPart(int percent, int size); ///generowanie tablicy losowych wartości

    void displayArray (int size, T* array); ///wyświetla tablicę w konsoli
};

#endif //AIZO_PROJEKT_ARRAYMANAGER_H
