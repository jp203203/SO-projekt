#include <utility>
#include <iostream>
#include "Queue.h"

//kolejka priorytetowa na bazie kopca binarnego
Queue::Queue(int* array, int size) {
    this -> size = size;
    queue_arr = new rec[size];
    is_index_present = new bool[size]; //tablica mówiąca, czy dany indeks nadal znajduje się w kopcu
    arr_to_q_index = new int[size]; //tablica "tłumacząca" indeksy tablicy na indeksy kolejki - ułatwia dostęp

    for(int i = 0; i < size; i++){ //dodanie rekordów na podstawie podanej tablicy
        queue_arr[i].value = &array[i]; //wskaźnik na wartość - dostęp do zaktualizowanych wartości
        queue_arr[i].index = i; //indeks oryginalnej tablicy
        arr_to_q_index[i] = i;
        is_index_present[i] = true;
    }

    heapify(); //budowa kopca
}

Queue::~Queue() {
    delete[] queue_arr;
    delete[] is_index_present;
    delete[] arr_to_q_index;
}

//wyciągnięcie najmniejszej wartości, naprawa kopca w dół - jak w heapsort
int Queue::extract_min() {
    int min = queue_arr[0].index;
    std::swap(queue_arr[0], queue_arr[size - 1]);
    std::swap(arr_to_q_index[queue_arr[0].index], arr_to_q_index[queue_arr[size - 1].index]);
    is_index_present[queue_arr[size - 1].index] = false;
    size--;
    fix_down(0);

    return min;
}

bool Queue::is_empty() {
    return (size == 0);
}

bool Queue::contains_index(int index) {
    return (is_index_present[index]);
}

//naprawa kolejki po aktualizacji wartości
void Queue::fix_queue(int index) {
    int queue_index = arr_to_q_index[index];
    fix_up(queue_index);
}

//budowa kopca
void Queue::heapify() {
    int parent_index = (size - 1) / 2;

    while(parent_index >= 0) {
        fix_down(parent_index);
        parent_index--;
    }
}

//naprawa w dół
void Queue::fix_down(int parent_index) {
    int smallest_index = parent_index;

    int lc_index = 2 * parent_index + 1;
    int rc_index = lc_index + 1;

    if(lc_index < size && *queue_arr[lc_index].value < *queue_arr[smallest_index].value) smallest_index = lc_index;
    if(rc_index < size && *queue_arr[rc_index].value < *queue_arr[smallest_index].value) smallest_index = rc_index;

    if(smallest_index != parent_index) {
        std::swap(queue_arr[parent_index], queue_arr[smallest_index]);
        std::swap(arr_to_q_index[queue_arr[parent_index].index], arr_to_q_index[queue_arr[smallest_index].index]);
        fix_down(smallest_index);
    }
}

//naprawa w górę
void Queue::fix_up(int child_index) {
    int parent_index = (child_index - 1) / 2;

    if(child_index > 0 && *queue_arr[parent_index].value > *queue_arr[child_index].value) {
        std::swap(queue_arr[parent_index], queue_arr[child_index]);
        std::swap(arr_to_q_index[queue_arr[parent_index].index], arr_to_q_index[queue_arr[child_index].index]);
        fix_up(parent_index);
    }
}