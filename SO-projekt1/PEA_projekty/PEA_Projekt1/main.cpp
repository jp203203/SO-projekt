#include <iostream>
#include "FileManager.h"
#include "GraphGenerator.h"
#include "BruteForce.h"
#include "BnBLittle.h"
#include "Dynamic.h"
#include "Interface.h"
#include "Timer.h"


int main() {
    FileManager file_manager;
    GraphGenerator generator;
    BruteForce brute_force;
    BnBLittle little;
    Dynamic dynamic;
    Timer timer;

    Interface interface(file_manager, generator, brute_force, little, timer, dynamic);
    interface.welcomeScreen();

    return 0;
}
