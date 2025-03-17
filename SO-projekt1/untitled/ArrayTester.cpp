#include "ArrayTester.h"

ArrayTester::ArrayTester(){};

bool ArrayTester::issortcorrect(int *array, int size) {

    bool issortcorrect = true;

    for(int i = 1; i < size; ++i){
        if(array[i] < array[i-1]){
            issortcorrect = false;
            break;
        }
    }

    return issortcorrect;
}
