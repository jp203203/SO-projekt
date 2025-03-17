#include <valarray>
#include <iostream>
#include "Sorter.h"

template <typename T>
Sorter<T>::Sorter(){};

//sortowanie przez wstawianie rosnąco
template <typename T>
void Sorter<T>::insertsort(int size, T* array) {

    for(int i = 1; i < size; ++i){ //iteracja od 1. do ostatniego elementu tablicy
        T key = array[i]; //przypisywanie wartości elementu kluczowi
        int j = i;

        //porównywanie wartości elementów na poprzednich pozycjach, dopóki nie dojdzie się do pierwszej pozycji, albo
        //element na pozycji bezpośrednio poprzedzającej nie jest mniejszy od wartości klucza
        while(j > 0 && array[j-1] > key){
            array[j] = array[j-1]; //przesuwanie elementu "w prawo"
            j--; //przejście na kolejną pozycję
        }

        array[j] = key; //przypisanie wartości klucza do ostatniej pozycji, której element został przesunięty
    }
}

//sortowanie przez wstawianie malejąco
template <typename T>
void Sorter<T>::insertsortdesc(int size, T* array) {

    for(int i = 1; i < size; ++i){ //iteracja od 1. do ostatniego elementu tablicy
        T key = array[i]; //przypisywanie wartości elementu kluczowi
        int j = i;

        //porównywanie wartości elementów na poprzednich pozycjach, dopóki nie dojdzie się do pierwszej pozycji, albo
        //element na pozycji bezpośrednio poprzedzającej nie jest większy od wartości klucza
        while(j > 0 && array[j-1] < key){
            array[j] = array[j-1]; //przesuwanie elementu "w prawo"
            j--; //przejście na kolejną pozycję
        }

        array[j] = key; //przypisanie wartości klucza do ostatniej pozycji, której element został przesunięty
    }
}

//sortowanie Shella - sekwencja Shella
template <typename T>
void Sorter<T>::shellsort1(int size, T* array) {

    int gapsize;
    int k = 1; //ustawienie k jako 1

    while(true){
        gapsize = size/pow(2, k); // odstęp wyliczany jako floor(n/2^k)
        if(gapsize == 0) return; //koniec pętli, gdy rozmiar odstępu jest równy 0

        //implementacja algorytmu przez wstawianie
        for(int i = gapsize; i < size; i++){ //wybranie drugiego elementu podtablicy - pod indeksem (gapsize)
            T key = array[i];
            int j = i;

            while(j >= gapsize && array[j-gapsize] > key){
                array[j] = array[j-gapsize]; //przesunięcie elementu "w prawo" - zgodnie z wyznaczonym odstępem
                j-=gapsize; //przejście na kolejną pozycję
            }

            array[j] = key;
        }

        k++; //inkrementacja k
    }
}

//sortowanie Shella - sekwencja Hibbarda
template <typename T>
void Sorter<T>::shellsort2(int size, T* array) {

    int gapsize;
    int k = log2(size); //ustawienie k jako logarytm o podstawie 2 z rozmiaru tablicy

    while(true){
        gapsize = pow(2, k) - 1; // odstęp wyliczany jako 2^k - 1
        if(gapsize == 0) return; //koniec pętli, gdy rozmiar odstępu jest równy 0

        //implementacja algorytmu przez wstawianie
        for(int i = gapsize; i < size; i++){
            T key = array[i];
            int j = i;

            while(j >= gapsize && array[j-gapsize] > key){
                array[j] = array[j-gapsize]; //przesunięcie elementu "w prawo" - zgodnie z wyznaczonym odstępem
                j-=gapsize; //przejście na kolejną pozycję
            }

            array[j] = key;
        }

        k--; //dekrementacja k
    }
}

//sortowanie szybkie
template <typename T>
void Sorter<T>::quicksort(int l, int r, T* array, int pchoice)
{
    if(l>=r) return;

    int m = partition(array, l, r, pchoice); //funkcja partition wyznacza indeks podziału tablicy

    //rekurencyjne wywołanie funkcji dla dwóch utworzonych podtablic
    quicksort(l, m, array, pchoice);
    quicksort(m+1, r, array, pchoice);
}

//funkcja partition
template <typename T>
int Sorter<T>::partition(T* array, int l, int r, int pchoice) {

    T pivot;

    switch(pchoice){ //wyznaczanie pivota na podstawie sposobu wybierania pivota
        case 1:
            pivot = array[l]; //pivot skrajnie lewy
            break;
        case 2:
            pivot = array[r]; //pivot skrajnie prawy
            break;
        case 3:
            pivot = array[(int)(l+r)/2]; //pivot środkowy
            break;
        case 4:
            pivot = array[static_cast<int>(rand() % (r-l+1))+l]; //pivot losowy
    }

    //"wskaźniki" skrajnych pozycji w tablicy
    int left = l;
    int right = r;

    while(true) {
        //przesuwanie lewego i prawego wskaźnika, dopóki nie natrafią na element mniejszy lub większy od pivota odpowiednio
        while(array[left] < pivot) ++left;
        while(array[right] > pivot) --right;

        //zamiana elementów pod lewym i prawym wskaźnikiem, gdy "miną się"
        if(left < right) {
            std::swap(array[left], array[right]);
            ++left;
            --right;
        }else {
            if(r == right) right--;
            return right;
        }
    }
}

template <typename T>
void Sorter<T>::buildheap(int size, T* array) {

    int parent = (size-1-1)/2;

    while(parent >= 0){
        heapfixdown(array, parent, size);
        parent--;
    }
}

//naprawa algorytmu w dół
template <typename T>
void Sorter<T>::heapfixdown(T* array, int parent, int size) {

    int largest = parent; //ustawianie indeksu największego elementu na rodzica
    int lch = parent*2 + 1; //lewy potomek
    int rch = lch + 1; //prawy potomek

    if(lch < size && array[lch] > array[largest]) largest = lch; //porównanie lewego potomka z największym elementem

    if(rch < size && array[rch] > array[largest]) largest = rch; //porównanie prawego potomka z największym elementem


    if(largest != parent){
        //gdy rodzic nie jest największym elementem, zamień miejscami rodzica i największy element
        std::swap(array[parent], array[largest]);
        //wywołanie rekurencyjne funkcji dla kolejnego poziomu drzewa
        heapfixdown(array, largest, size);
    }
}

//sortowanie przez kopcowanie
template <typename T>
void Sorter<T>::heapsort(int size, T* array) {

    buildheap(size, array); //zbuduj kopiec

    size--; //zmniejsz rozmiar tablicy o 1

    while(size > 0){ //pętla wykonuje się do momentu, aż rozmiar tablicy nie wyniesie 0
        //zamieniaj element ostatni z pierwszym
        std::swap(array[0], array[size]);
        //napraw kopiec
        heapfixdown(array, 0, size);
        //zmniejsz rozmiar tablicy o 1
        size--;
    }
}

template class Sorter<int>;
template class Sorter<float>;
