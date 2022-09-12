#pragma once

#include <iostream>
#include <thread>
#ifdef _WIN32
    #include <windows.h>
#endif
#include <queue>
#include <vector>
#include <list>
#include <math.h>
#include <chrono>
#include <algorithm>
#include "nbi.h"
#include "elevatordata.hpp"
#include "entitydata.hpp"

using namespace std;

extern vector<ElevatorData>windy;
extern vector<EntityData>byty;

extern int ile_wind;
extern int ile_bytow;

//FUNKCJA SPRAWDZA CZY STRUKTURA elements ZAWIERA LICZBÊ needle
template<class T>
bool czy_zawiera(const T& elements, int needle)
{
    return std::find(elements.begin(), elements.end(), needle) != elements.end();
}

//FUNKCJA ZATRZYMUJE WYWOLUJACY JA W¥TEK
void spij(int time);

//void setCursor(int x, int y)
//{
//     COORD c;
//     c.X = x-1;
//     c.Y = y-1;
//     SetConsoleCursorPosition (GetStdHandle (STD_OUTPUT_HANDLE), c);
//}

//FUNKCJA CZYŒCI TERMINAL
void czyszczenie();


