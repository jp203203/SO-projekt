#include <cstdlib>
#include <ctime>
#include <iostream>
#include "ArrayManager.h"

ArrayManager::ArrayManager(){
    srand(time(0));
}

int* ArrayManager::genRandArr(int size){
    int* array = new int[size];

    for(int i = 0; i < size; ++i){
        array[i] = static_cast<int>(rand() % size*1.5);
    }

    return array;
}

int* ArrayManager::genRandArrPart(int percent, int size) {
    int* array = new int[size];

    int sortedpart = size * (percent/100.0);

    for(int i = 0; i < sortedpart; ++i){
        array[i] = i;
    }
    std::cout<<"sorted part = "<<size<<std::endl;

    for(int i = sortedpart; i < size; ++i){
        array[i] = static_cast<int>(rand() % size*1.5) + sortedpart;
    }

    return array;
}

void ArrayManager::displayArray(int size, int *array){
    for(int i = 0; i < size; ++i){
        std::cout<<array[i]<<", ";
    }
    std::cout<<std::endl;
}