#include "utilities.hpp"

vector<ElevatorData>windy;
vector<EntityData>byty;
int ile_bytow=0;
int ile_wind;
//Buffer buffer;

Object* basic;
ShaderProgram* program;

int window_width;
int window_height;

float cursor_x;
float cursor_y;

int number_keys_state[10];
int enter_key_state;
int backspace_key_state;
int left_mouse_state;

float time_since_logic_update=0;



void spij(int time)
{
    this_thread::sleep_for(std::chrono::milliseconds(time));
}


void czyszczenie()
{
        #ifdef _WIN32
            system ("cls");
        #endif

        #ifdef __linux__
            system("clear");
        #endif
}

float szerokosc_bezwzgledna(float pixel_width)
{
    return pixel_width/window_width;
}

float wysokosc_bezwzgledna(float pixel_height)
{
    return pixel_height/window_height;
}

int napis_na_liczbe(string a)
{
    int number;
    stringstream ss;

    ss<<a;
    ss>>number;

    return number;
}

