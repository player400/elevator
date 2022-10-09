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
#include <functional>
#include <cstdlib>
#include <string>
#include <sstream>

#include "nbi.h"
#include "elevatordata.hpp"
#include "entitydata.hpp"
#include "winx.h"
#include "glad/glad.h"
#include "buffer.hpp"
#include "shader.hpp"
#include "stb_image.h"
#include "texture.hpp"
#include "texturebuffer.hpp"





using namespace std;

extern vector<ElevatorData>windy;
extern vector<EntityData>byty;

extern int ile_wind;
extern int ile_bytow;

extern int window_width;
extern int window_height;

extern float cursor_x;
extern float cursor_y;


extern int number_keys_state[10];

extern int enter_key_state;

extern int backspace_key_state;

extern int left_mouse_state;



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

//FUNKCJA OTRZYMUJE SZEROKOSC W PIKSELACH I ZWRACA ULAMEK INFORMUJACY JAKA TO CZESC SZEROKOSCI CALEGO OKNA
float szerokosc_bezwzgledna(float pixel_width);

//FUNKCJA OTRZYMUJE WYSOKOSC W PIKSELACH I ZWRACA ULAMEK INFORMUJACY JAKA TO CZESC WYSOKOSCI CALEGO OKNA
float wysokosc_bezwzgledna(float pixel_height);

//FUNKCJA OTRZYMUJE CYFRE I ZWRACA ZNAK JEJ ODPOWIADAJACY
char cyfra_na_znak(int number);


