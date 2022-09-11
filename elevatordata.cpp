
using namespace std;

#include "utilities.hpp"

int ile_wind;

int ElevatorData::minimum()
{
    return *std::min_element(polecenia.begin(), polecenia.end());
}


int ElevatorData::maksimum()
{
    return *std::max_element(polecenia.begin(), polecenia.end());
}

void ElevatorData::dodaj_polecenie(int w)
{
    polecenia.push_back(w);
}


void ElevatorData::dodaj_przystanek(int w)
{
    przystanki.push_back(w);
}


void ElevatorData::wyswietl(int i)
{
    cout<<"Elevator "<<i<<":"<<endl;
    switch(status)
    {
        case UP : {cout<<"underway, using engine"<<endl<<"door closed"<<endl;} break;
        case DOWN : {cout<<"underway, using gravity"<<endl<<"door closed"<<endl;} break;
        case STOP : {cout<<"full stop"<<endl<<"door open"<<endl;} break;
    }

    cout<<last_floor_number<<endl;
//  cout<<current_destination<<endl;
//  for(int i=0;i<polecenia.size();i++)
//  {
//      cout<<polecenia[i]<<" ";
//  }
    if((status==UP)||(status==DOWN))
    {
        underway_status++;
        for(int j=0;j<underway_status;j++)
        {
            cout<<".";
        }
    }
    cout<<endl<<endl;
}


void ElevatorData::zmien_pietro()
{
    if(status==UP)
    {
        last_floor_number++;
    }

    if(status==DOWN)
    {
        last_floor_number--;
    }

    underway_status=0;

    if(last_floor_number==current_destination)
    {
        cooldown=5;
        status=STOP;
        polecenia.erase(polecenia.begin());
    }

    if(czy_zawiera(przystanki,last_floor_number))
    {
        cooldown=5;
        status=STOP;
        przystanki.remove(last_floor_number);
    }
}


bool ElevatorData::czy_jedzie(int w)
{

    if(czy_zawiera(przystanki,w))
    {
        return true;
    }


    if(czy_zawiera(polecenia,w))
    {
        return true;
    }

    return (last_floor_number==w)&&(status==STOP);
}



void ElevatorData::dodaj_komende(int w)
{


    if(polecenia.size()==0)
    {
        dodaj_polecenie(w);
        is_stop_detected=NO_INFO;
        return;
    }


    switch(is_stop_detected)
    {
        case NO_INFO:
        {
            int far_points[3];
            far_points[0]=last_floor_number;
            far_points[1]=minimum();
            far_points[2]=maksimum();

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
                dodaj_przystanek(w);
            }
            else
            {
                dodaj_polecenie(w);
            }
        }; break;

        case YES:
        {
            dodaj_przystanek(w);
        }; break;

        case NO:
        {
            dodaj_polecenie(w);
        }; break;

    }

    is_stop_detected=NO_INFO;
}


//FUNKCJA OBLICZAJACA JAK DELAKO WINDA MUSIALABY JECHAC ABY DOTRZEC NA PIETRO int==w Z UWZGLEDNIENIEM direction I INNYCH POLECEN DANEJ WINDY
int ElevatorData::dystans(int w, char direction)
{
    int distance;

    if(polecenia.size()==0)
    {
        distance=abs(last_floor_number-w);
        return distance;
    }


    if((polecenia[0]>w && last_floor_number<w && direction=='u')||(polecenia[0]<w && last_floor_number>w && direction=='d'))
    {
        is_stop_detected=YES;
        distance=abs(w-last_floor_number);
        return distance;
    }
    else
    {
        distance=abs(last_floor_number-polecenia[0]);
    }

    for(int j=0;j<(polecenia.size()-1);j++)
    {
        if((polecenia[j]<w && polecenia[j+1]>w && direction=='u') || (polecenia[j]>w && polecenia[j+1]<w && direction=='d'))
        {
            distance=distance+abs(polecenia[j]-w);
            is_stop_detected=YES;
            return distance;
        }
        else
        {
            distance=distance+abs(polecenia[j]-polecenia[j+1]);
        }
    }

    return distance+abs(polecenia[polecenia.size()-1]-w);
}



//AKTUALIZACJA DANYCH WINDY
void ElevatorData::aktualizuj(int i)
{
    if(cooldown==0)
    {

        if(!polecenia.empty())
        {
            current_destination=polecenia[0];

        }

        if(last_floor_number>current_destination)
        {
            status=DOWN;

        }

        if(last_floor_number<current_destination)
        {
            status=UP;
        }

        if(underway_status==5)
        {
            zmien_pietro();
        }
    }
    else{cooldown=cooldown-1;}

    wyswietl(i);

}



bool czy_jedzie(int numerwindy, int numerpietra)
{
    if(numerwindy==-1)
    {
        for(int i=0;i<ile_wind;i++)
        {
            return windy[i].czy_jedzie(numerpietra);
        }
        return false;
    }

    return windy[numerwindy].czy_jedzie(numerpietra);

}



void wywolaj_winde(int numer_windy, int w, char direction)
{
    //JESLI PODANO NUMER KONKRETNEJ WINDY TO FUNKCJA NIE SPRAWDZA distance
    if(numer_windy!=-1)
    {
        windy[numer_windy].dodaj_komende(w);
        return;
    }

    if(ile_wind==1)
    {
        windy[0].dodaj_komende(w);
        return;
    }

    int minimum_distance;
    int numer_optymalnej_windy=0;

    for(int i=0;i<ile_wind;i++)
    {

        int distance=windy[i].dystans(w, direction);

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

    windy[numer_optymalnej_windy].dodaj_komende(w);

}
