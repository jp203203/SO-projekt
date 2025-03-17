#include <iostream>

int *create_array(int length);

void generate_permutations(int* array, int length);

void print_permutation(int* array, int length, int counter);

int main() {
    int length;
    std::cout<<"Podaj dlugosc tablicy:\n";
    std::cin>>length;

    int* array = create_array(length);

    generate_permutations(array, length);
    print_permutation(array, length, 0);

    delete[] array;
    return 0;
}

void print_permutation(int* array, int length, int counter) {
    for(int i = 0; i < length; i++) {
        std::cout<<array[i]<<" ";
    }
    std::cout<<"\n";
}

int* create_array(int length) {
    int* new_array = new int[length];

    for(int i = 0; i < length; i++) {
        new_array[i] = i;
    }

    return new_array;
}

void generate_permutations(int* array, int length) {
    int* C = new int[length];
    //int* cut_array = new int[length - 1];

    for(int i = 0; i < length; i++) {
        C[i] = 1;
    }

    int counter = 1;
    print_permutation(array, length, counter);

    //std::copy(array + 1, array + length, cut_array);

    int k = 1;
    while(k < length) {
        if(C[k] < k) {
            if(k % 2 == 1) {
                std::swap(array[1], array[k]);
            } else {
                std::swap(array[C[k]], array[k]);
            }

            //std::copy(cut_array, cut_array + length - 1, array + 1);
            counter++;
            print_permutation(array, length, counter);

            C[k]++;
            k = 1;
        } else {
            C[k] = 1;
            k++;
        }
    }

    delete[] C;
}
