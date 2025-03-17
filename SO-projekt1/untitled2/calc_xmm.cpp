#include <iostream>
#include <chrono>
using namespace std;

void add_cpp(int* vals1, int* vals2){
    for(int i = 0; i < 4; i++){
        int res = vals1[i] + vals2[i];
    }
}

void sub_cpp(int* vals1, int* vals2){
    for(int i = 0; i < 4; i++){
        int res = vals1[i] - vals2[i];
    }
}

void mul_cpp(int* vals1, int* vals2){
    for(int i = 0; i < 4; i++){
        int res = vals1[i] * vals2[i];
    }
}

void div_cpp(int* vals1, int* vals2){
    for(int i = 0; i < 4; i++){
        int res = vals1[i] / vals2[i];
    }
}

void add_asm(int* vals1, int* vals2){
    asm (
            "movdqu (%0), %%xmm0;"
            "movdqu (%1), %%xmm1;"
            "paddd %%xmm1, %%xmm0;"
            :
            : "r"(vals1), "r"(vals2)
            : "%xmm0", "%xmm1"
            );
}

void sub_asm(int* vals1, int* vals2){
    asm (
            "movdqu (%0), %%xmm0;"
            "movdqu (%1), %%xmm1;"
            "psubd %%xmm1, %%xmm0;"
            :
            : "r"(vals1), "r"(vals2)
            : "%xmm0", "%xmm1"
            );
}

auto mul_asm(int* vals1, int* vals2){
    asm (
            "movdqu (%0), %%xmm0;"
            "movdqu (%1), %%xmm1;"
            "pmulld %%xmm1, %%xmm0;"
            :
            : "r"(vals1), "r"(vals2)
            : "%xmm0", "%xmm1"
            );
}

auto div_asm(int* vals1, int* vals2){
    asm (
            "movdqu (%0), %%xmm0;"
            "movdqu (%1), %%xmm1;"
            "cvtdq2ps %%xmm0, %%xmm0;"
            "cvtdq2ps %%xmm1, %%xmm1;"
            "divps %%xmm1, %%xmm0;"
            "cvtps2dq %%xmm0, %%xmm0;"
            :
            : "r"(vals1), "r"(vals2)
            : "%xmm0", "%xmm1"
            );
}

void measure_time(void (*operation)(int*, int*), int reps){
    chrono::duration<double, micro> sum(0);

    for(int i = 0; i < reps; i++){
        int vals1[4], vals2[4];

        for(int j = 0; j < 4; j++) {
            vals1[j] = rand() % 1000 + 1;
            vals2[j] = rand() % 1000 + 1;
        }

        auto start = chrono::high_resolution_clock::now();
        operation(vals1, vals2);
        auto end = chrono::high_resolution_clock::now();

        sum += std::chrono::duration_cast<std::chrono::duration<double, std::micro>>(end - start);
    }

    cout<<"Czas wykonania dzialan: "<<sum.count() << " us" << endl;
}

int main(){
    srand(time(NULL));
    int reps, op_type, method;
    cout<<"Podaj ilosc powtorzen:\n";
    cin>>reps;

    std::cout<<"Podaj dzialanie:\n"
             <<"1. dodawanie\n"
             <<"2. odejmowanie\n"
             <<"3. mnozenie\n"
             <<"4. dzielenie\n";
    std::cin>>op_type;

    std::cout<<"Podaj metode wykonania dzialan:\n"
             <<"1. C++\n"
             <<"2. assembler\n";
    std::cin>>method;

    switch(op_type){
        case 1:
            switch(method) {
                case 1:
                    measure_time(add_cpp, reps);
                    break;
                case 2:
                    measure_time(add_asm, reps);
                    break;
            }
            break;
        case 2:
            switch(method) {
                case 1:
                    measure_time(sub_cpp, reps);
                    break;
                case 2:
                    measure_time(sub_asm, reps);
                    break;
            }
            break;
        case 3:
            switch(method) {
                case 1:
                    measure_time(mul_cpp, reps);
                    break;
                case 2:
                    measure_time(mul_asm, reps);
                    break;
            }
            break;
        case 4:
            switch(method) {
                case 1:
                    measure_time(div_cpp, reps);
                    break;
                case 2:
                    measure_time(div_asm, reps);
                    break;
            }
            break;
    }
    return 0;
}