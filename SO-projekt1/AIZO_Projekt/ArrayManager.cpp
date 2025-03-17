#include <cstdlib>
#include <ctime>
#include <iostream>
#include "ArrayManager.h"

template <typename T>
ArrayManager<T>::ArrayManager(){
    srand(time(0));
}

//metoda generująca tablice losowe
template <typename T>
T* ArrayManager<T>::genRandArr(int size){
    T* array = new T[size]; //tworzenie tablicy

    for(int i = 0; i < size; ++i){ //generowanie losowych elementów dla pozostałej części tablicy
        //generowanie elementów typu float z zakresu od 0 do (rozmiar tablicy * 1,5)
        float element = ((rand()) / static_cast <float> (RAND_MAX))* size * 1.5;
        array[i] = static_cast<T>(element); //rzutowanie typu na element i umieszczanie go w tablicy
    }

    return array;
}

//metoda generująca tablice posortowane częściowo lub w całości
template <typename T>
T* ArrayManager<T>::genRandArrPart(int percent, int size) {
    T* array = new T[size]; //tworzenie tablicy

    int sortedpart = size * (percent/100.0); //obliczanie, ile procentowo elementów w tablicy ma być posortowanych

    for(T i = 0; i < sortedpart; ++i){ //wypełnienie posortowanej części tablicy kolejnymi liczbami rosnącymi o 1
        array[static_cast<int>(i)] = i;
    }

    for(int i = sortedpart; i < size; ++i){ //generowanie losowych elementów dla pozostałej części tablicy
        //generowanie elementów typu float z zakresu od 0 do (rozmiar tablicy * 1,5 + część posortowana)
        float element = ((rand()) / static_cast <float> (RAND_MAX))* size * 1.5 + sortedpart;
        array[i] = static_cast<T>(element); //rzutowanie typu na element i umieszczanie go w tablicy
    }

    return array;
}

template <typename T>
void ArrayManager<T>::displayArray(int size, T* array){
    for(int i = 0; i < size; ++i){
        std::cout<<array[i]<<", ";
    }
    std::cout<<std::endl;
}

template class ArrayManager<int>;
template class ArrayManager<float>;