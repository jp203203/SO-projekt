#include <iostream>
#include <chrono>

void add_int(int v1, int v2){
    asm (
            "movl %0, %%eax;"
            "addl %1, %%eax;"
            :
            : "r" (v1), "r" (v2)
            : "%eax"
            );
}

void sub_int(int v1, int v2){
    asm (
            "movl %0, %%eax;"
            "subl %1, %%eax;"
            :
            : "r" (v1), "r" (v2)
            : "%eax"
            );
}

void mul_int(int v1, int v2){
    asm (
            "movl %0, %%eax;"
            "mull %1;"
            :
            : "r" (v1), "r" (v2)
            : "%eax"
            );
}

void div_int(int v1, int v2){
    asm (
            "movl %0, %%eax;"
            "divl %1;"
            :
            : "r" (v1), "r" (v2)
            : "%eax", "%edx"
            );
}

void add_float(float v1, float v2){
    asm (
            "flds (%0);"
            "fadds (%1);"
            :
            : "r" (&v1), "r" (&v2)
            : "st(1)", "st(2)"
            );
}

void sub_float(float v1, float v2){
    asm (
            "flds (%0);"
            "fsubs (%1);"
            :
            : "r" (&v1), "r" (&v2)
            : "st(1)", "st(2)"
            );
}

void mul_float(float v1, float v2){
    asm (
            "flds (%0);"
            "fmuls (%1);"
            :
            : "r" (&v1), "r" (&v2)
            : "st(1)", "st(2)"
            );
}

void div_float(float v1, float v2){
    asm (
            "flds (%0);"
            "fdivs (%1);"
            :
            : "r" (&v2), "r" (&v1)
            : "st(1)", "st(2)"
            );
}

void int_operation(int reps, void (*operation)(int, int)){
    std::chrono::duration<double, std::micro> sum(0);
    for(int i = 0; i < reps; i++){
        int v1 = rand() % 1000 + 1;
        int v2 = rand() % 1000 + 1;

        auto start = std::chrono::high_resolution_clock::now();
        operation(v1, v2);
        auto end = std::chrono::high_resolution_clock::now();

        sum += std::chrono::duration_cast<std::chrono::duration<double, std::micro>>(end - start);
    }

    std::cout<<"Czas wykonania dzialan: "<<sum.count() << " us" << std::endl;
}

void float_operation(int reps, void (*operation)(float, float)){
    std::chrono::duration<double, std::micro> sum(0);
    for(int i = 0; i < reps; i++){
        float v1 = (float)(rand() % 10000) / 10.0;
        float v2 = (float)(rand() % 10000) / 10.0;

        auto start = std::chrono::high_resolution_clock::now();
        operation(v1, v2);
        auto end = std::chrono::high_resolution_clock::now();

        sum += std::chrono::duration_cast<std::chrono::duration<double, std::micro>>(end - start);
    }

    std::cout<<"Czas wykonania dzialan: "<<sum.count() << " us" << std::endl;
}

int main() {
    srand(time(NULL));
    int reps, num_type, op_type;

    std::cout<<"Podaj ilosc powtorzen dzialania:\n";
    std::cin>>reps;

    std::cout<<"Podaj typ danych:\n"
            <<"1. int\n"
            <<"2. float\n";
    std::cin>>num_type;

    std::cout<<"Podaj dzialanie:\n"
             <<"1. dodawanie\n"
             <<"2. odejmowanie\n"
             <<"3. mnozenie\n"
             <<"4. dzielenie\n";
    std::cin>>op_type;

    if(reps < 1){
        std::cout<<"Niepoprawny parametr!";
        return 1;
    }

    switch(num_type){
        case 1:
            switch(op_type){
                case 1:
                    int_operation(reps, add_int);
                    break;
                case 2:
                    int_operation(reps, sub_int);
                    break;
                case 3:
                    int_operation(reps, mul_int);
                case 4:
                    int_operation(reps, div_int);
                default:
                    std::cout<<"Niepoprawny parametr!";
                    return 1;
            }
            break;
        case 2:
            switch(op_type){
                case 1:
                    float_operation(reps, add_float);
                    break;
                case 2:
                    float_operation(reps, sub_float);
                    break;
                case 3:
                    float_operation(reps, mul_float);
                case 4:
                    float_operation(reps, div_float);
                default:
                    std::cout<<"Niepoprawny parametr!";
                    return 1;
            }
            break;
        default:
            std::cout<<"Niepoprawny parametr!";
            return 1;
    }

    return 0;
}

