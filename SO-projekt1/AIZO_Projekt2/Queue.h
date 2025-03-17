#ifndef AIZO_PROJEKT2_QUEUE_H
#define AIZO_PROJEKT2_QUEUE_H


class Queue {
private:
    struct rec {
        int index;
        int* value;
    };

    int size;
    rec* queue_arr;
    bool* is_index_present;
    int* arr_to_q_index;

    void heapify();
    void fix_down(int parent_index);
    void fix_up(int child_index);

public:
    Queue(int* array, int size);
    ~Queue();

    int extract_min();
    bool is_empty();
    bool contains_index(int index);

    void fix_queue(int index);
};


#endif //AIZO_PROJEKT2_QUEUE_H
