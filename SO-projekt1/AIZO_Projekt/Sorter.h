#ifndef AIZO_PROJEKT_SORTER_H
#define AIZO_PROJEKT_SORTER_H

template <typename T>
class Sorter {
public:
    Sorter();

    void insertsort(int size, T* array); ///algorytm sortowania przez wstawianie
    void insertsortdesc(int size, T* array); ///algorytm sortowania przez wstawianie malejąco

    void shellsort1(int size, T* array); ///algorytm sortowania Shella z oryginalnym algorytmem odstępów
    void shellsort2(int size, T* array); ///algorytm sortowania Shella z algorytmem odstępów Hibbarda

    void quicksort(int l, int r, T* array, int pchoice); ///algorytm sortowania szybkiego - z wyborem pivota

    void heapsort(int size, T* array); ///algorytm sortowania przez kopcowanie

private:
    int partition(T* array, int l, int r, int pchoice);
    void buildheap(int size, T* array);
    void heapfixdown(T* array, int parent, int size);

};


#endif //AIZO_PROJEKT_SORTER_H
