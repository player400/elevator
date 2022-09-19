using namespace std;

#include "utilities.hpp"
#include "elevatordata.hpp"
#include "entitydata.hpp"


char EntityData::kierunek(int difference)
{
    if(difference>0)
    return 'u';
    return 'd';
}

void EntityData::wyswietl()
{
    cout<<"Passenger "<<l<<":"<<endl;
    switch(status)
    {
        case WAITING : {cout<<"waiting in the hallway"<<endl;} break;
        case UNDERWAY : {cout<<"onboard the elevator"<<endl;} break;
    }
    cout<<"Going from floor "<<origin<<" to floor "<<destination<<endl;
    cout<<endl;
}

EntityData::EntityData(int orig, int dest, int id)
{
    l=id;
    destination=dest;
    origin=orig;
    elevator_number=wywolaj_winde(-1, origin, kierunek(destination-origin));
    status=WAITING;
    should_remove=false;
}

void EntityData::aktualizuj()
{
    if(windy[elevator_number].czy_stoi(destination))
    {
        should_remove=true;
    }

    if(windy[elevator_number].czy_stoi(origin))
    {
        wywolaj_winde(elevator_number, destination, 'u');
        status=UNDERWAY;
    }

    wyswietl();
}



