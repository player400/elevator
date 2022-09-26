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
#include "winx.h"
#include "glad/glad.h"
#include "buffer.hpp"
#include "shader.hpp"
#include "stb_image.h"
#include "texture.hpp"
#include "writing.hpp"


using namespace std;

extern vector<ElevatorData>windy;
extern vector<EntityData>byty;

extern int ile_wind;
extern int ile_bytow;

//extern Buffer buffer;
//FUNKCJA SPRAWDZA CZY STRUKTURA elements ZAWIERA LICZBE needle
template<class T>
bool czy_zawiera(const T& elements, int needle)
{
    return std::find(elements.begin(), elements.end(), needle) != elements.end();
}

//FUNKCJA ZATRZYMUJE WYWOLUJACY JA WATEK
void spij(int time);

//void setCursor(int x, int y)
//{
//     COORD c;
//     c.X = x-1;
//     c.Y = y-1;
//     SetConsoleCursorPosition (GetStdHandle (STD_OUTPUT_HANDLE), c);
//}

//FUNKCJA CZYSCI TERMINAL
void czyszczenie();


