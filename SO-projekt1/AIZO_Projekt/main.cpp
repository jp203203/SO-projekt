#include <iostream>
#include "Interface.h"

using namespace std;

int main() {

    //inicjalizacja interfejsów dla dwóch typów danych
    Interface<int> interfacei;
    Interface<float> interfacef;

    cout<<"Program sortujacy\n";

    int typechoice;
    cout<<"\nJakiego typu maja byc elementy tablic?\n";
    cout<<"1. int\n";
    cout<<"2. float\n";

    typechoice = interfacei.optioninput(2);
    system("cls");

    //w zależności od wyboru typu danych, korzystaj z odpowiedniego interfejsu
    if(typechoice == 1){
        interfacei.displayinterface();
    } else{
        interfacef.displayinterface();
    }
}
