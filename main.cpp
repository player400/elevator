//EURO ELEVATOR Simulator Licence Agreement:
//
//COPYRIGHT (c) 2022 player400
//
//PLEASE FOLLOW THE FOLLOWING RULES WHILE USING, SHARING, DISTRIBUTING, CHANGING ETC. MY CODE:
//1. F*CK YOU THIEF, GO WRITE YOUR OWN CODE
//2. YOU CANT? GO CRY TO YOUR MOMMY
//3. JUST JOKING, GO TO pasjainformatyki.pl AND LEARN TO MAKE NOT-SO-COOL SOFTWARE YOURSELF!
//4. But actually idc I'd need to be a moron to write a licence for few hundred lines of code and legal stuff is boring anyway - just do whatever you want with it
//5. HAVE FUN :-)
//6. PS - I am not responsible for anything anyone uses my software for. If it breaks down your machine (higly unlikely), it's your problem. I do not guarantee anything concerning this code.


#include <iostream>
#include <thread>
#define NBI_LIB_IMPLEMENTATION
#ifdef _WIN32
    #include <windows.h>
#endif
#include <queue>
#include <list>
#include <math.h>
#include <chrono>
#include <conio.h>
using namespace std;


//THIS IS THE CODE WRITTEN BY magistermaks, who kindly asks all it's users to attach a licence agreement to it.
//As you are about to see he's really serious about licence agreements and does not like to implement "jokes" in the licence.
//
//* MIT License
//*
//* Copyright (c) 2020 magistermaks
//*
//* Permission is hereby granted, free of charge, to any person obtaining a copy
//* of this software and associated documentation files (the "Software"), to deal
//* in the Software without restriction, including without limitation the rights
//* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//* copies of the Software, and to permit persons to whom the Software is
//* furnished to do so, subject to the following conditions:
//*
//* The above copyright notice and this permission notice shall be included in all
//* copies or substantial portions of the Software.
//*
//* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// * SOFTWARE.

#ifdef NBI_LIB_WINDOWS
#define __NBI_LIB_WINDOWS
#elif defined NBI_LIB_LINUX
#define __NBI_LIB_LINUX
#else
#ifdef _WIN32
#define __NBI_LIB_WINDOWS
#elif defined __APPLE__
#define __NBI_LIB_LINUX
#elif defined __linux__
#define __NBI_LIB_LINUX
#elif defined __unix__
#define __NBI_LIB_LINUX
#else
#error "Build environment test failed. Define NBI_LIB_WINDOWS or NBI_LIB_LINUX."
#endif
#endif

#ifndef __NBI_HEADER
#define __NBI_HEADER

#ifndef NBI_LIB_ASSUME_STDIO
#include <stdio.h>
#endif

#ifdef __NBI_LIB_WINDOWS
#include <conio.h>
#endif

#ifdef __NBI_LIB_LINUX
#include <sys/types.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#ifndef NBI_LIB_ASSUME_TERMIOS
#include <termios.h>
#endif
#endif

#ifdef __NBI_LIB_WINDOWS
#define NBI_KEY_ESC 27
#define NBI_KEY_TAB 9
#define NBI_KEY_BACKSPACE 8
#define NBI_KEY_ENTER 13
#define NBI_KEY_SPACE 32
#endif

#ifdef __NBI_LIB_LINUX
#define NBI_KEY_ESC 27
#define NBI_KEY_TAB 9
#define NBI_KEY_BACKSPACE 8
#define NBI_KEY_ENTER 10
#define NBI_KEY_SPACE 32
#endif

#define NBI_KEY_NONE -1

#ifdef __cplusplus
extern "C" {
#endif

char nbi_get_char();
bool nbi_get_flag();
char nbi_std_input();
void nbi_set_echo( bool echo );
void nbi_clear();
void nbi_wait();

#ifdef __NBI_LIB_LINUX
void __nbi_termios_init();
void __nbi_termios_push();
void __nbi_termios_pop();

void nbi_termios_update();
#endif

extern bool __nbi_echo;
#ifdef __NBI_LIB_LINUX
extern struct termios __nbi_termios_state_required;
extern struct termios __nbi_termios_state_current;
extern bool __nbi_termios_initialized;
extern bool __nbi_termios_state;
#endif

#ifdef __cplusplus
}
#endif

#endif

#ifdef NBI_LIB_IMPLEMENTATION
#undef NBI_LIB_IMPLEMENTATION

#ifdef __cplusplus
extern "C" {
#endif

bool __nbi_echo = false;

#ifdef __NBI_LIB_LINUX
struct termios __nbi_termios_state_required;
struct termios __nbi_termios_state_current;
bool __nbi_termios_initialized = false;
bool __nbi_termios_state = false;

void __nbi_termios_init() {
    tcgetattr(0, &__nbi_termios_state_required);
    __nbi_termios_state_current = __nbi_termios_state_required;
    __nbi_termios_state_required.c_lflag &= ~ICANON;
    nbi_set_echo( __nbi_echo );
    __nbi_termios_push();
}

void __nbi_termios_push() {
    if( __nbi_termios_state ) return;
    __nbi_termios_state = true;
    tcsetattr(0, TCSANOW, &__nbi_termios_state_required);
}

void __nbi_termios_pop() {
    __nbi_termios_state = false;
    tcsetattr(0, TCSANOW, &__nbi_termios_state_current);
}

void nbi_termios_update() {
    tcgetattr(0, &__nbi_termios_state_current);
}
#endif

char nbi_get_char() {
    if( nbi_get_flag() )
        return nbi_std_input();
    else
        return -1;
}

bool nbi_get_flag() {
#ifdef __NBI_LIB_WINDOWS
    return (bool)_kbhit();
#elif defined __NBI_LIB_LINUX
    if( !__nbi_termios_initialized ){
        __nbi_termios_init();
    }
    __nbi_termios_push();

    timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;

    fd_set fd;
    FD_ZERO(&fd);
    FD_SET(0, &fd);

    bool flag = (bool)select(1, &fd, NULL, NULL, &timeout);
#ifndef NBI_LIB_NO_TERMIOS_POP
    __nbi_termios_pop();
#endif
    return flag;
#endif
}

char nbi_std_input() {
#ifdef __NBI_LIB_WINDOWS
    if( __nbi_echo )
        return _getche();
    else
        return _getch();
#elif defined __NBI_LIB_LINUX
    if( !__nbi_termios_initialized ){
        __nbi_termios_init();
    }
    __nbi_termios_push();
    char chr = getchar();
#ifndef NBI_LIB_NO_TERMIOS_POP
    __nbi_termios_pop();
#endif
    return chr;
#endif
}

void nbi_set_echo( bool echo ) {
    __nbi_echo = echo;
#ifdef __NBI_LIB_LINUX
    __nbi_termios_state = false;
    if( echo )
        __nbi_termios_state_required.c_lflag |= ECHO;
    else
        __nbi_termios_state_required.c_lflag &= ~ECHO;
#endif
}

void nbi_clear() {
    while( nbi_get_flag() ) nbi_get_char();
}

void nbi_wait() {
    nbi_std_input();
}

#ifdef __cplusplus
}
#endif

#endif
//THE magistermaks'es PORTION OF THE SOFTWARE THEREBY ENDS, JUST AS HIS OUTRAGEOUS, RESTRICTIVE AND OVERALL BORING LICENCE AGREEMENT
//FROM NOW ON YOU MAY COPY WHATEVER YOU WANT FROM THE CODE AND I DONT GIVE A SHIT ABOUT IT
//DETAILS ARE PROVIDED ON TOP OF THE CODE IN THE EES LICENCE AGREEMENT


volatile bool wstrzymywanie=false;
int ilewind;

struct ElevatorData
{
    vector<int>polecenia;
    list<int>przystanki;
    int last_floor_number=0;
    int current_destination;
    int underway_status=0;
    int cooldown=0;

    enum status_
    {
        UP,
        DOWN,
        STOP
    };

    status_ status;


};

 vector<ElevatorData>windy;

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

int minimum(int liczba_polecen, int i)
{
    auto& winda=windy[i];
    int wynik=winda.polecenia[0];
    for(int i=0;i<liczba_polecen;i++)
    {
        if(winda.polecenia[i]<wynik)
        {
            wynik=winda.polecenia[i];
        }
    }
    return wynik;
}

int maksimum(int liczba_polecen, int i)
{
    auto& winda=windy[i];
    int wynik=winda.polecenia[0];
    for(int i=0;i<liczba_polecen;i++)
    {
        if(winda.polecenia[i]>wynik)
        {
            wynik=winda.polecenia[i];
        }
    }
    return wynik;
}


bool czy_zawiera(std::list<int>& elements, int neadle)
{
    for(int element : elements)
    {
        if(element == neadle) return true;
    }
    return false;
}

bool czy_jedzie_konkretna(int i, int w)
{
    auto& winda=windy[i];

    if(czy_zawiera(winda.przystanki,w))
    {
        return true;
    }

    for(int j=0;j<winda.polecenia.size();j++)
    {
        if(winda.polecenia[j]==w)
        {
            return true;
        }
    }

    return (winda.last_floor_number==w)&&(winda.status==ElevatorData::STOP);


}


bool czy_jedzie(int numerwindy, int numerpietra)
{
    if(numerwindy==-1)
    {
        for(int i=0;i<ilewind;i++)
        {
            return czy_jedzie_konkretna(i, numerpietra);
        }
        return false;
    }

    return czy_jedzie_konkretna(numerwindy, numerpietra);

}

int dystans(int w, int liczba_polecen, char direction, ElevatorData winda, bool*pointer)
{
    int distance;

    if(liczba_polecen==0)
    {
        distance=abs(winda.last_floor_number-w);
        return distance;
    }


    if((winda.polecenia[0]>w && winda.last_floor_number<w && direction=='u')||(winda.polecenia[0]<w && winda.last_floor_number>w && direction=='d'))
    {
        *pointer=true;
        distance=abs(w-winda.last_floor_number);
        return distance;
    }
    else
    {
        distance=abs(winda.last_floor_number-winda.polecenia[0]);
    }

    for(int j=0;j<(liczba_polecen-1);j++)
    {
        if((winda.polecenia[j]<w && winda.polecenia[j+1]>w && direction=='u') || (winda.polecenia[j]>w && winda.polecenia[j+1]<w && direction=='d'))
        {
            distance=distance+abs(winda.polecenia[j]-w);
            *pointer=true;
            return distance;
        }
        else
        {
            distance=distance+abs(winda.polecenia[j]-winda.polecenia[j+1]);
        }
    }


    distance=distance+abs(winda.polecenia[liczba_polecen-1]-w);

    return distance;
}


void wywolanie_dowolnej_windy(int w, char direction)
{

    int liczba_polecen[ilewind];
    for(int i=0;i<ilewind;i++)
    {
        liczba_polecen[i]=windy[i].polecenia.size();
    }

    bool stop_found[ilewind];
    int minimum_distance;
    int numer_optymalnej_windy=0;

    for(int i=0;i<ilewind;i++)
    {
        auto& winda=windy[i];
        stop_found[i]=false;
        bool*pointer;
        pointer=&stop_found[i];

        int distance=dystans(w, liczba_polecen[i], direction, winda, pointer);

        if(i==0)
        {
            minimum_distance=distance;
        }

        if(distance<minimum_distance)
        {
            minimum_distance=distance;
            numer_optymalnej_windy=i;
        }
    }

    if(stop_found[numer_optymalnej_windy]==true)
    {
        windy[numer_optymalnej_windy].przystanki.push_back(w);
    }
    else
    {
        windy[numer_optymalnej_windy].polecenia.push_back(w);
    }

}

void polecenie_konkretnej_windy(int w, int numer_windy)
{
    int liczba_polecen[ilewind];
    for(int i=0;i<ilewind;i++)
    {
        liczba_polecen[i]=windy[i].polecenia.size();
    }

    auto& winda=windy[numer_windy];

    if(liczba_polecen[numer_windy]==0)
    {
        winda.polecenia.push_back(w);
    }
    else
    {
        int far_points[3];
        far_points[0]=winda.last_floor_number;
        far_points[1]=minimum(liczba_polecen[numer_windy], numer_windy);
        far_points[2]=maksimum(liczba_polecen[numer_windy], numer_windy);

        for(int k=0;k<2;k++)
        {
            if(far_points[k]>far_points[k+1])
            {
                int intermediary=far_points[k];
                far_points[k]=far_points[k+1];
                far_points[k+1]=intermediary;
            }
        }

        if( w>far_points[0] && w<far_points[2] )
        {
            winda.przystanki.push_back(w);
        }
        else
        {
            winda.polecenia.push_back(w);
        }
    }
}

void sterowanie()
{

    cout<<"Launching the Sandbox mode..."<<endl;
    for(int i=0;i<20;i++)
    {
        cout<<"/  ";
        this_thread::sleep_for(std::chrono::milliseconds(45));
    }

    while(true)
    {
        if(nbi_get_flag())
        {
            wstrzymywanie=true;
            int numer_windy;
            cin>>numer_windy;
            int w;
            cin>>w;

//WYWOLANIE OGOLNE (PRZYWOŁANIE WINDY Z HOLU)
            if(numer_windy==-1)
            {
                char direction;
                cin>>direction;

                if(czy_jedzie(-1, w))
                {
                    wstrzymywanie=false;
                    continue;
                }

                wywolanie_dowolnej_windy(w, direction);
            }



//NADANIE POLECENIA KONKRETNEJ WINDZIE (WYBÓR PIĘTRA Z WINDY)
            else
            {

                if(czy_jedzie(numer_windy, w))
                {
                    wstrzymywanie=false;
                    continue;
                }

                polecenie_konkretnej_windy(w, numer_windy);

            }

            wstrzymywanie=false;
        }
    }
}

int main()
{

    cout<<"Welcome to EURO ELEVATOR Simulator 1.0"<<endl;
    cout<<"Press 1 to launch the Sandbox Mode"<<endl;
    int modenumber=0;
    char menu;
    menu=nbi_std_input();
    switch (menu)
    {
        case '1': {cout<<"Welcome to Sandbox Mode!"<<endl<<endl;modenumber=1;} break;
    }

    czyszczenie();

    cout<<"CONTROLS:"<<endl<<endl;
    cout<<"To simulate calling an elevator from the hallway type: -1 <floor number> <direction>. Direction is either u - for going up or d - for going down."<<endl;
    cout<<"This command will call the nearest elevator to the floor chosen."<<endl<<endl;
    cout<<"To simulate sending a specific elevator somewhere using buttons in the elevator type <elevator number> <floor number>"<<endl<<endl;
    cout<<"To start type the number of elevators you want to simulate and click Enter. Have fun!"<<endl;

    cin>>ilewind;

    for(int i=0;i<ilewind;i++)
    {
        ElevatorData pustawinda;
        pustawinda.status = ElevatorData::STOP;
        pustawinda.last_floor_number = 0;
        pustawinda.current_destination = 0;
        windy.push_back(pustawinda);
    }

    czyszczenie();

    thread t1(sterowanie);

    wstrzymywanie=false;

    while(true)
    {
        this_thread::sleep_for(std::chrono::milliseconds(1000));

        while(wstrzymywanie)
        {
             this_thread::sleep_for(std::chrono::milliseconds(10));

        }

        czyszczenie();

        for(int i=0;i<ilewind;i++)
        {

            if(windy[i].cooldown==0)
            {

                if(!windy[i].polecenia.empty())
                {
                    windy[i].current_destination=windy[i].polecenia[0];

                }

                if(windy[i].last_floor_number>windy[i].current_destination)
                {
                    windy[i].status=ElevatorData::DOWN;

                }

                if(windy[i].last_floor_number<windy[i].current_destination)
                {
                    windy[i].status=ElevatorData::UP;
                }



                if(windy[i].underway_status==5)
                {
                    if(windy[i].status==ElevatorData::UP)
                    {
                        windy[i].last_floor_number++;
                    }

                    if(windy[i].status==ElevatorData::DOWN)
                    {
                        windy[i].last_floor_number--;
                    }

                    windy[i].underway_status=0;

                    if(windy[i].last_floor_number==windy[i].current_destination)
                    {
                        windy[i].cooldown=5;

                        windy[i].status=ElevatorData::STOP;
                        windy[i].polecenia.erase(windy[i].polecenia.begin());

                    }




                    if(czy_zawiera(windy[i].przystanki,windy[i].last_floor_number))
                    {
                        windy[i].cooldown=5;

                        windy[i].status=ElevatorData::STOP;
                        windy[i].przystanki.remove(windy[i].last_floor_number);
                    }

                }
            }
            else{windy[i].cooldown=windy[i].cooldown-1;}

            cout<<"Elevator "<<i<<":"<<endl;
            switch(windy[i].status)
            {
                case ElevatorData::UP : {cout<<"underway, using engine"<<endl<<"door closed"<<endl;} break;
                case ElevatorData::DOWN : {cout<<"underway, using gravity"<<endl<<"door closed"<<endl;} break;
                case ElevatorData::STOP : {cout<<"full stop"<<endl<<"door open"<<endl;} break;
            }

            cout<<windy[i].last_floor_number<<endl;
//          cout<<current_destination<<endl;
//          for(int i=0;i<polecenia.size();i++)
//          {
//              cout<<polecenia[i]<<" ";
//          }
            if((windy[i].status==ElevatorData::UP)||(windy[i].status==ElevatorData::DOWN))
            {
                windy[i].underway_status++;
                for(int j=0;j<windy[i].underway_status;j++)
                {
                    cout<<".";
                }
            }
            cout<<endl<<endl;
        }
        cout<<"Type commands here:";
    }
    return 0;
}

