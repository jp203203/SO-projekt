#include "Timer.h"

//Klasa pomiaru czasu z możliwością ustawienia czasu początkowego, czasu zatrzymania, oraz zwrócenia różnicy pomiędzy nimi
Timer::Timer() {}

void Timer::start() {
    startTime = chrono::high_resolution_clock::now();
}

void Timer::stop() {
    endTime = chrono::high_resolution_clock::now();
}

double Timer::getTime() const {
    return chrono::duration<double>(endTime - startTime).count();
}
