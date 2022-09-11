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

using namespace std;

extern vector<ElevatorData>windy;

extern int ile_wind;

template<class T>
bool czy_zawiera(const T& elements, int needle)
{
    return std::find(elements.begin(), elements.end(), needle) != elements.end();
}

void spij(int time);


//void setCursor(int x, int y)
//{
//     COORD c;
//     c.X = x-1;
//     c.Y = y-1;
//     SetConsoleCursorPosition (GetStdHandle (STD_OUTPUT_HANDLE), c);
//}

void czyszczenie();


