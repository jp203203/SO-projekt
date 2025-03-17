#include <iostream>
#include "Graph.h"
#include "FileManager.h"
#include "NearestNeighbor.h"
#include "SimAnnealing.h"
#include "TabuSearch.h"
#include "Interface.h"

int main() {
    //inicjalizacja obiektów potrzebnych klas oraz odpalenie interfejsu
    NearestNeighbor nn;
    SimAnnealing sa;
    TabuSearch ts;
    FileManager fm;

    Interface interface(fm, nn, sa, ts);
    interface.menuScreen();

    return 0;
}
