#ifndef UNTITLED_ARRAYMANAGER_H
#define UNTITLED_ARRAYMANAGER_H

#include <cstdlib>
#include <ctime>

class ArrayManager{
public:
    ArrayManager();

    int* genRandArr(int size); ///generowanie tablicy losowych wartości
    int* genRandArrPart(int percent, int size); ///generowanie tablicy losowych wartości

    void displayArray (int size, int* array); ///wyświetla tablicę w konsoli
};

#endif //UNTITLED_ARRAYMANAGER_H
