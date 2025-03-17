#include "Interface.h"
#include "FileManager.h"
#include "MST.h"
#include "ShortestPath.h"
#include "GraphGenerator.h"
#include "Timer.h"

using namespace std;

int main() {        //stworzenie obiektów klas i wywołanie interfejsu użytkownika
    MST mst;
    ShortestPath sp;
    FileManager fm;
    GraphGenerator gg;
    Timer timer;

    Interface ui(fm, mst, sp, gg, timer);
    ui.welcomeScreen();
    return 0;
}

