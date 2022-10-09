#include "utilities.hpp"

vector<ElevatorData>windy;
vector<EntityData>byty;
int ile_bytow=0;
int ile_wind;
//Buffer buffer;

int window_width;
int window_height;

float cursor_x;
float cursor_y;

int number_keys_state[10];
int enter_key_state;
int backspace_key_state;
int left_mouse_state;

void spij(int time)
{
    this_thread::sleep_for(std::chrono::milliseconds(time));
}

//void setCursor(int x, int y)
//{
//     COORD c;
//     c.X = x-1;
//     c.Y = y-1;
//     SetConsoleCursorPosition (GetStdHandle (STD_OUTPUT_HANDLE), c);
//}

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

char cyfra_na_znak(int number)
{
    switch(number)
    {
        case 0: return '0'; break;
        case 1: return '1'; break;
        case 2: return '2'; break;
        case 3: return '3'; break;
        case 4: return '4'; break;
        case 5: return '5'; break;
        case 6: return '6'; break;
        case 7: return '7'; break;
        case 8: return '8'; break;
        case 9: return '9'; break;
    }
    return 'a';
}

