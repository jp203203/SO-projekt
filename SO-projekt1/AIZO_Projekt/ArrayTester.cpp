#include "ArrayTester.h"

template <typename T>
ArrayTester<T>::ArrayTester(){};

template <typename T>
bool ArrayTester<T>::issortcorrect(T* array, int size) {

    bool issortcorrect = true;

    for(int i = 1; i < size; ++i){ //zaczynając od 2. elementu, sprawdzaj czy jest większy od poprzedniego
        if(array[i] < array[i-1]){
            issortcorrect = false; //jeżeli nie jest, zakończ pętle i zwróć false
            break;
        }
    }

    return issortcorrect;
}

template class ArrayTester<int>;
template class ArrayTester<float>;