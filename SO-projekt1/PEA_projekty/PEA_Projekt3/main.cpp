#include "FileManager.h"
#include "NearestNeighbor.h"
#include "SimAnnealing.h"
#include "TabuSearch.h"
#include "GeneticAlgorithm.h"
#include "Interface.h"

int main() {
    // inicjalizacja obiektów potrzebnych klas oraz odpalenie interfejsu
    NearestNeighbor nn;
    SimAnnealing sa;
    TabuSearch ts;
    GeneticAlgorithm ga;
    FileManager fm;

    Interface interface(fm, nn, sa, ts, ga);
    interface.menuScreen();

    return 0;
}
