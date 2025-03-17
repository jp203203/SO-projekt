#include <valarray>
#include <iostream>
#include "Sorter.h"

Sorter::Sorter(){};

void Sorter::insertsort(int size, int *array) {

    for(int i = 1; i < size; ++i){
        int key = array[i];
        int j = i;

        while(j > 0 && array[j-1] > key){
            array[j] = array[j-1];
            j--;
        }

        array[j] = key;
    }
}

void Sorter::insertsortdesc(int size, int *array) {

    for(int i = 1; i < size; ++i){
        int key = array[i];
        int j = i;

        while(j > 0 && array[j-1] < key){
            array[j] = array[j-1];
            j--;
        }

        array[j] = key;
    }
}

void Sorter::shellsort1(int size, int* array) {

    int gapsize;
    int k = 1;

    while(true){
        gapsize = size/pow(2, k);
        if(gapsize == 0) return;
        std::cout<<"odstep = "<<gapsize<<"\n";

        for(int i = gapsize; i < size; i++){
            int key = array[i];
            int j = i;

            while(j >= gapsize && array[j-gapsize] > key){
                array[j] = array[j-gapsize];
                j-=gapsize;
            }

            array[j] = key;
        }

        k++;
    }
}

void Sorter::shellsort2(int size, int* array) {

    int gapsize;
    int k = log2(size);

    while(true){
        gapsize = pow(2, k) - 1;
        if(gapsize == 0) return;
        std::cout<<"odstep = "<<gapsize<<"\n";

        for(int i = gapsize; i < size; i++){
            int key = array[i];
            int j = i;

            while(j >= gapsize && array[j-gapsize] > key){
                array[j] = array[j-gapsize];
                j-=gapsize;
            }

            array[j] = key;
        }

        k--;
    }
}

void Sorter::quicksort(int l, int r, int *array, int pchoice)
{
    if(l>=r) return;

    int m = partition(array, l, r, pchoice);
    quicksort(l, m, array, pchoice);
    quicksort(m+1, r, array, pchoice);
}

int Sorter::partition(int *array, int l, int r, int pchoice) {

    int pivot;

    switch(pchoice){
        case 1:
            pivot = array[l];
            break;
        case 2:
            pivot = array[r];
            break;
        case 3:
            pivot = array[(int)(l+r)/2];
            break;
        case 4:
            pivot = array[static_cast<int>(rand() % (r-l+1))+l];
    }

    int left = l;
    int right = r;

    while(true) {
        while(array[left] < pivot) ++left;
        while(array[right] > pivot) --right;

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

void Sorter::buildheap(int size, int *array) {

    int parent = (size-1-1)/2;

    while(parent >= 0){
        heapfixdown(array, parent, size);
        parent--;
    }
}

void Sorter::heapfixdown(int *array, int parent, int size) {

    int largest = parent;
    int lch = parent*2 + 1;
    int rch = lch + 1;

    if(lch < size && array[lch] > array[largest]) largest = lch;

    if(rch < size && array[rch] > array[largest]) largest = rch;


    if(largest != parent){
        std::swap(array[parent], array[largest]);
        heapfixdown(array, largest, size);
    }
}

void Sorter::heapsort(int size, int *array) {

    buildheap(size, array);

    size--;

    while(size > 0){
        std::swap(array[0], array[size]);
        heapfixdown(array, 0, size);
        size--;
    }
}


