#include "utilities.hpp"

vector<ElevatorData>windy;
vector<EntityData>byty;
int ile_bytow=0;
int ile_wind;
//Buffer buffer;

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

