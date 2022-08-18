#include <iostream>
#include <thread>
#ifdef _WIN32
#include <windows.h>
#endif
#include <queue>
#include <list>
#include <math.h>
#include <chrono>
using namespace std;


vector<int>polecenia;
list<int>przystanki;
int last_floor_number=0;
 int current_destination=0;

 enum struct ElevatorData
 {
     UP,
     DOWN,
     STOP
 };

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

int minimum(int liczba_polecen)
{
    int wynik=polecenia[0];
    for(int i=0;i<liczba_polecen;i++)
    {
        if(polecenia[i]<wynik)
        {
            wynik=polecenia[i];
        }
    }
    return wynik;
}

int maksimum(int liczba_polecen)
{
   int wynik=polecenia[0];
    for(int i=0;i<liczba_polecen;i++)
    {
        if(polecenia[i]>wynik)
        {
            wynik=polecenia[i];
        }
    }
    return wynik;
}

void sterowanie()
{
    while(true)
    {
        int numer_windy;
        cin>>numer_windy;
        int w;
        cin>>w;

        int liczba_polecen=polecenia.size();

        //WYWOLANIE OGOLNE (PRZYWO£ANIE WINDY Z HOLU)
        if(numer_windy==-1)
        {
            char direction;
            cin>>direction;
            int jedzie=0;

            //PRZY DODAWANIU WIND KONIECZNA ZMIANA WARUNKU PÊTLI ORAZ UZALE¯NIENIA ZMIENNYCH OD ITOERATORA PÊTLI (NP. przystanki[j].elevator[i]==w)
            for(int i=0;i<1;i++)
            {

                    if(contains(przystanki,w))
                    {
                        jedzie=1;

                    }



                for(int j=0;j<liczba_polecen;j++)
                {
                    if(polecenia[j]==w)
                    {
                        jedzie=1;
                        break;
                    }

                }
            }

            if(jedzie==1)
            {
                continue;
            }
            else
            {

                int distance[1];
                int znalezionoprzystanek[1];

                //KOLEJNA PÊTLA DO ZMIANY, NALE¯Y ZMIENIÆ RÓWNIE¯ TABLICE distance ORAZ znalezionoprzystanek PRZY WIELU WINDACH TRZEBA BÊDZIE DODAÆ INDEXY DO WSZYSTKICH ZMIENNYCH
                //PÊTLA MUSI ITEROWAÆ SIÊ TYLE RAZY ILE JEST WIND
                for(int i=0;i<1;i++)
                {
                    znalezionoprzystanek[i]=0;
                    distance[i]=0;
                    if(liczba_polecen==0)
                    {
                        distance[i]=abs(last_floor_number-w);
                        continue;
                    }

                    //PRIORYTET WINDY - JAZDA W GÓRÊ
                    if(direction=='u')
                    {
                        if(liczba_polecen==1)
                        {
                            if((polecenia[0]>w)&&(last_floor_number<w))
                            {
                                znalezionoprzystanek[i]=1;
                                distance[i]=abs(w-last_floor_number);
                            }
                        }


                        for(int j=0;j<(liczba_polecen-1);j++)
                        {
                            if((polecenia[j]<w)&&(polecenia[j+1]>w))
                            {
                                distance[i]=distance[i]+abs(polecenia[j]-w);
                                znalezionoprzystanek[i]=1;
                                break;
                            }
                            else
                            {
                                distance[i]=distance[i]+abs(polecenia[j]-polecenia[j+1]);
                            }

                        }

                        if(znalezionoprzystanek[i]==0)
                        {
                            distance[i]=distance[i]+abs(w-polecenia[liczba_polecen-1]);
                        }

                    }


                    //PRIORYTET WINDY - JAZDA W DÓ£
                     if(direction=='d')
                    {
                        if(liczba_polecen==1)
                        {
                            if((polecenia[0]<w)&&(last_floor_number>w))
                            {
                                znalezionoprzystanek[i]=1;
                                distance[i]=abs(w-last_floor_number);
                            }
                        }

                        for(int j=0;j<(liczba_polecen-1);j++)
                        {
                            if((polecenia[j]>w)&&(polecenia[j+1]<w))
                            {
                                distance[i]=distance[i]+abs(polecenia[j]-w);
                                znalezionoprzystanek[i]=1;
                                break;
                            }
                            else
                            {
                                distance[i]=distance[i]+abs(polecenia[j]-polecenia[j+1]);
                            }

                        }

                          if(znalezionoprzystanek[i]==0)
                        {
                            distance[i]=distance[i]+abs(w-polecenia[liczba_polecen-1]);
                        }

                    }
                }

                //TUTAJ MUSI BYÆ WYSZUKIWANIE NAJMNIEJSZEGO ELEMENTU Z TABLICY distance W CELU OPTYMALIZACJI TRASY !!!!!!!


                if(znalezionoprzystanek[0]==1)
                {
                    przystanki.push_back(w);
                }
                else
                {
                    polecenia.push_back(w);
                }
            }
        }

        //NADANIE POLECENIA KONKRETNEJ WINDZIE (WYBÓR PIÊTRA Z WINDY)
        else
        {
                int jedzie=0;

            //PRZY DODAWANIU WIND KONIECZNA ZMIANA WARUNKU PÊTLI ORAZ UZALE¯NIENIA ZMIENNYCH OD ITOERATORA PÊTLI (NP. przystanki[j].elevator[i]==w)


                    if(contains(przystanki,w))
                    {
                        jedzie=1;

                    }



                for(int j=0;j<liczba_polecen;j++)
                {
                    if(polecenia[j]==w)
                    {
                        jedzie=1;
                        break;
                    }

                }

        if(jedzie==1)
            {
                continue;
            }



            else
            {
                if(liczba_polecen==0)
                {
                    polecenia.push_back(w);
                }
                else
                {
                    if(((maksimum(liczba_polecen)>w)&&(minimum(liczba_polecen)<w))||((maksimum(liczba_polecen)>w)&&(last_floor_number<w))||((last_floor_number>w)&&(minimum(liczba_polecen)<w)))
                    {
                        przystanki.push_back(w);
                    }
                    else
                    {
                        polecenia.push_back(w);
                    }
                }
            }
        }


      //  polecenia.push_back(w);
    }
}

int main()
{

cout<<"Welcome to EURO ELEVATOR Simulator BETA"<<endl;
cout<<"Press 1 and click Enter to launch the Sandbox Mode"<<endl;
char menu;
cin>>menu;



thread t1(sterowanie);

 ElevatorData status=ElevatorData::STOP;


 int underway_Status=0;

 int current_destination=0;
 int cooldown=0;

    while(true)
    {
        #ifdef _WIN32
            system ("cls");
        #endif

        #ifdef __linux__
            system("clear");
        #endif
           //setCursor(0,0);
        cout<<"Elevator 0:"<<endl;
        switch(status)
        {
            case ElevatorData::UP : {cout<<"underway, using engine"<<endl<<"door closed"<<endl;} break;
            case ElevatorData::DOWN : {cout<<"underway, using gravity"<<endl<<"door closed"<<endl;} break;
            case ElevatorData::STOP : {cout<<"full stop"<<endl<<"door open"<<endl;} break;
        }

        cout<<last_floor_number<<endl;
//        cout<<current_destination<<endl;
//        for(int i=0;i<polecenia.size();i++)
//        {
//            cout<<polecenia[i]<<" ";
//        }
        this_thread::sleep_for(std::chrono::milliseconds(1000));
        if(cooldown==0)
        {

        if(!polecenia.empty())
        {
          current_destination=polecenia[0];

        }

        if(last_floor_number>current_destination)
        {
          status=ElevatorData::DOWN;

        }

        if(last_floor_number<current_destination)
        {
            status=ElevatorData::UP;

        }

        if((status==ElevatorData::UP)||(status==ElevatorData::DOWN))
        {
            underway_Status++;
            for(int i=0;i<underway_Status;i++)
            {
            cout<<".";
            }
        }

        if(underway_Status==5)
        {
            if(status==ElevatorData::UP)
            {
                last_floor_number++;
            }

            if(status==ElevatorData::DOWN)
            {
                last_floor_number=last_floor_number-1;
            }

            underway_Status=0;

            if(last_floor_number==current_destination)
            {
                cooldown=5;

                status=ElevatorData::STOP;
                polecenia.erase(polecenia.begin());

            }




                if(contains(przystanki,last_floor_number))
                {
                    cooldown=5;

                    status=ElevatorData::STOP;
                    przystanki.remove(last_floor_number);
                }

        }
        }
        else{cooldown=cooldown-1;}

    }


}
