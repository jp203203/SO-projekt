#ifndef UNTITLED_SORTER_H
#define UNTITLED_SORTER_H


class Sorter {
public:
    Sorter();

    void insertsort(int size, int* array); ///algorytm sortowania przez wstawianie
    void insertsortdesc(int size, int* array); ///algorytm sortowania przez wstawianie malejąco

    void shellsort1(int size, int* array); ///algorytm sortowania Shella z oryginalnym algorytmem odstępów
    void shellsort2(int size, int* array); ///algorytm sortowania Shella z algorytmem odstępów Hibbarda

    void quicksort(int l, int r, int* array, int pchoice); ///algorytm sortowania szybkiego - z wyborem pivota

    void heapsort(int size, int* array); ///algorytm sortowania przez kopcowanie

private:
    int partition(int* array, int l, int r, int pchoice);
    void buildheap(int size, int* array);
    void heapfixdown(int* array, int parent, int size);

};


#endif //UNTITLED_SORTER_H
