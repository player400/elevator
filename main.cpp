//EURO ELEVATOR Simulator Licence Agreement:
//
//COPYRIGHT (c) 2022 player400
//
//PLEASE FOLLOW THE FOLLOWING RULES WHILE USING, SHARING, DISTRIBUTING, CHANGING ETC. MY CODE:
//1. F*CK YOU THIEF, GO WRITE YOUR OWN CODE
//2. YOU CANT? GO CRY TO YOUR MOMMY
//3. JUST JOKING, GO TO pasjaprogramowania.pl AND LEARN TO MAKE NOT-SO-COOL SOFTWARE YOURSELF!
//4. But actually idc I'd need to be a moron to write a licence for 300 lines of code and legal stuff is boring anyway - just do whatever you want with it
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


bool freezerdata=false;


struct ElevatorData
{
    vector<int>polecenia;
    list<int>przystanki;
    int last_floor_number=0;
    int current_destination=0;

    enum status_
    {
        UP,
        DOWN,
        STOP
    };

    status_ status=status_::STOP;


};

 ElevatorData windy[2];

//void setCursor(int x, int y)
//{
//     COORD c;
//     c.X = x-1;
//     c.Y = y-1;
//     SetConsoleCursorPosition (GetStdHandle (STD_OUTPUT_HANDLE), c);
//}

bool contains(std::list<int>& elements, int neadle)
{
    for(int element : elements)
    {
        if(element == neadle) return true;
    }
    return false;
}

int minimum(int liczba_polecen, int winda)
{
    int wynik=windy[winda].polecenia[0];
    for(int i=0;i<liczba_polecen;i++)
    {
        if(windy[winda].polecenia[i]<wynik)
        {
            wynik=windy[winda].polecenia[i];
        }
    }
    return wynik;
}

int maksimum(int liczba_polecen, int winda)
{
   int wynik=windy[winda].polecenia[0];
    for(int i=0;i<liczba_polecen;i++)
    {
        if(windy[winda].polecenia[i]>wynik)
        {
            wynik=windy[winda].polecenia[i];
        }
    }
    return wynik;
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
            freezerdata=true;
            int numer_windy;
//          cout<<".";
            cin>>numer_windy;
            int w;
            cin>>w;

            int liczba_polecen[2];
            for(int i=0;i<2;i++)
            {
                liczba_polecen[i]=windy[i].polecenia.size();
            }

//WYWOLANIE OGOLNE (PRZYWOŁANIE WINDY Z HOLU)
            if(numer_windy==-1)
            {
                char direction;
                cin>>direction;
                int jedzie=0;

//PRZY DODAWANIU WIND KONIECZNA ZMIANA WARUNKU PĘTLI ORAZ UZALEŻNIENIA ZMIENNYCH OD ITOERATORA PĘTLI (NP. przystanki[j].elevator[i]==w)
                for(int i=0;i<2;i++)
                {

                    if(contains(windy[i].przystanki,w))
                    {
                        jedzie=1;

                    }



                    for(int j=0;j<liczba_polecen[i];j++)
                    {
                        if(windy[i].polecenia[j]==w)
                        {
                            jedzie=1;
                            break;
                        }

                    }
                }

                if(jedzie==1)
                {
                    freezerdata=false;
                    continue;
                }
                else
                {

                    int distance[2];
                    int znalezionoprzystanek[2];

//KOLEJNA PĘTLA DO ZMIANY, NALEŻY ZMIENIĆ RÓWNIEŻ TABLICE distance ORAZ znalezionoprzystanek PRZY WIELU WINDACH TRZEBA BĘDZIE DODAĆ INDEXY DO WSZYSTKICH ZMIENNYCH
//PĘTLA MUSI ITEROWAĆ SIĘ TYLE RAZY ILE JEST WIND
                    for(int i=0;i<2;i++)
                    {
                        znalezionoprzystanek[i]=0;
                        distance[i]=0;
                        if(liczba_polecen[i]==0)
                        {
                            distance[i]=abs(windy[i].last_floor_number-w);
                            continue;
                        }

//PRIORYTET WINDY - JAZDA W GÓRĘ
                        if(direction=='u')
                        {
                            if(liczba_polecen[i]==1)
                            {
                                if((windy[i].polecenia[0]>w)&&(windy[i].last_floor_number<w))
                                {
                                    znalezionoprzystanek[i]=1;
                                    distance[i]=abs(w-windy[i].last_floor_number);
                                }
                            }


                            for(int j=0;j<(liczba_polecen[i]-1);j++)
                            {
                                if((windy[i].polecenia[j]<w)&&(windy[i].polecenia[j+1]>w))
                                {
                                    distance[i]=distance[i]+abs(windy[i].polecenia[j]-w);
                                    znalezionoprzystanek[i]=1;
                                    break;
                                }
                                else
                                {
                                    distance[i]=distance[i]+abs(windy[i].polecenia[j]-windy[i].polecenia[j+1]);
                                }

                            }

                            if(znalezionoprzystanek[i]==0)
                            {
                                distance[i]=distance[i]+abs(w-windy[i].polecenia[liczba_polecen[i]-1]);
                            }

                        }

//PRIORYTET WINDY - JAZDA W DÓŁ
                        if(direction=='d')
                        {
                            if(liczba_polecen[i]==1)
                            {
                                if((windy[i].polecenia[0]<w)&&(windy[i].last_floor_number>w))
                                {
                                    znalezionoprzystanek[i]=1;
                                    distance[i]=abs(w-windy[i].last_floor_number);
                                }
                            }

                            for(int j=0;j<(liczba_polecen[i]-1);j++)
                            {
                                if((windy[i].polecenia[j]>w)&&(windy[i].polecenia[j+1]<w))
                                {
                                    distance[i]=distance[i]+abs(windy[i].polecenia[j]-w);
                                    znalezionoprzystanek[i]=1;
                                    break;
                                }
                                else
                                {
                                    distance[i]=distance[i]+abs(windy[i].polecenia[j]-windy[i].polecenia[j+1]);
                                }

                            }

                            if(znalezionoprzystanek[i]==0)
                            {
                                distance[i]=distance[i]+abs(w-windy[i].polecenia[liczba_polecen[i]-1]);
                            }

                        }
                    }

                    int numer_optymalnej_windy=0;
                    for(int i=0; i<2; i++)
                    {
                        if(distance[numer_optymalnej_windy]>distance[i])
                        {
                            numer_optymalnej_windy=i;
                        }
                    }
//TUTAJ MUSI BYĆ WYSZUKIWANIE NAJMNIEJSZEGO ELEMENTU Z TABLICY distance W CELU OPTYMALIZACJI TRASY !!!!!!!

//ZERA W TYM IFIE NALEŻY ZASTĄPIĆ NUMERAMI NAJBARDZIEJ OPTYMALNEJ WINDY
                    if(znalezionoprzystanek[numer_optymalnej_windy]==1)
                    {
                        windy[numer_optymalnej_windy].przystanki.push_back(w);
                    }
                    else
                    {
                        windy[numer_optymalnej_windy].polecenia.push_back(w);
                    }
                }
            }



//NADANIE POLECENIA KONKRETNEJ WINDZIE (WYBÓR PIĘTRA Z WINDY)
            else
            {
                int jedzie=0;

//PRZY DODAWANIU WIND KONIECZNA ZMIANA WARUNKU PĘTLI ORAZ UZALEŻNIENIA ZMIENNYCH OD ITOERATORA PĘTLI (NP. przystanki[j].elevator[i]==w)


                if(contains(windy[numer_windy].przystanki,w))
                {
                    jedzie=1;

                }



                for(int j=0;j<liczba_polecen[numer_windy];j++)
                {
                    if(windy[numer_windy].polecenia[j]==w)
                    {
                        jedzie=1;
                        break;
                    }

                }

                if(jedzie==1)
                {
                    freezerdata=false;
                    continue;
                }



                else
                {
                    if(liczba_polecen[numer_windy]==0)
                    {
                        windy[numer_windy].polecenia.push_back(w);
                    }
                    else
                    {
                        if(((maksimum(liczba_polecen[numer_windy], numer_windy)>w)&&(minimum(liczba_polecen[numer_windy], numer_windy)<w))||((maksimum(liczba_polecen[numer_windy], numer_windy)>w)&&(windy[numer_windy].last_floor_number<w))||((windy[numer_windy].last_floor_number>w)&&(minimum(liczba_polecen[numer_windy], numer_windy)<w)))
                        {
                            windy[numer_windy].przystanki.push_back(w);
                        }
                        else
                        {
                            windy[numer_windy].polecenia.push_back(w);
                        }
                    }
                }
            }


            //polecenia.push_back(w);
            freezerdata=false;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int main()
{

    cout<<"Welcome to EURO ELEVATOR Simulator 1.0"<<endl;
    cout<<"Press 1 and click Enter to launch the Sandbox Mode"<<endl;
    char menu;
    cin>>menu;
    #ifdef _WIN32
        system ("cls");
    #endif

    #ifdef __linux__
        system("clear");
    #endif


    thread t1(sterowanie);

    //ElevatorData status=ElevatorData::STOP;
    freezerdata=0;

    int underway_Status[2];
    for(int i=0;i<2;i++)
    {
        underway_Status[i]=0;
    }

    //int current_destination=0;
    int cooldown[2];
    for(int i=0;i<2;i++)
    {
        cooldown[i]=0;
    }

    while(true)
    {
        this_thread::sleep_for(std::chrono::milliseconds(1000));

        while(freezerdata)
        {
             this_thread::sleep_for(std::chrono::milliseconds(10));

        }
        #ifdef _WIN32
            system ("cls");
        #endif

        #ifdef __linux__
            system("clear");
        #endif


        //setCursor(0,0);

        for(int i=0;i<2;i++)
        {

            if(cooldown[i]==0)
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



                if(underway_Status[i]==5)
                {
                    if(windy[i].status==ElevatorData::UP)
                    {
                        windy[i].last_floor_number++;
                    }

                    if(windy[i].status==ElevatorData::DOWN)
                    {
                        windy[i].last_floor_number--;
                    }

                    underway_Status[i]=0;

                    if(windy[i].last_floor_number==windy[i].current_destination)
                    {
                        cooldown[i]=5;

                        windy[i].status=ElevatorData::STOP;
                        windy[i].polecenia.erase(windy[i].polecenia.begin());

                    }




                    if(contains(windy[i].przystanki,windy[i].last_floor_number))
                    {
                        cooldown[i]=5;

                        windy[i].status=ElevatorData::STOP;
                        windy[i].przystanki.remove(windy[i].last_floor_number);
                    }

                }
            }
            else{cooldown[i]=cooldown[i]-1;}

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
                underway_Status[i]++;
                for(int j=0;j<underway_Status[i];j++)
                {
                    cout<<".";
                }
            }
            cout<<endl<<endl;
        }
        cout<<"Type commands here:";
    }
}

