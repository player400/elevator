#pragma once

using namespace std;

class ElevatorData
{
    private:
        vector<int>polecenia;
        list<int>przystanki;
        int last_floor_number=0;
        int current_destination=0;
        int underway_status=0;
        int cooldown=0;

        enum is_stop_detected_
        {
            NO_INFO,
            YES,
            NO,
        };

        is_stop_detected_ is_stop_detected=NO_INFO;

        enum status_
        {
            UP,
            DOWN,
            STOP,
        };

        status_ status=STOP;



        int minimum();


        int maksimum();

        void dodaj_polecenie(int w);


        void dodaj_przystanek(int w);


        void wyswietl(int i);



        void zmien_pietro();


    public:

        bool czy_jedzie(int w);




        void dodaj_komende(int w);


//FUNKCJA OBLICZAJACA JAK DELAKO WINDA MUSIALABY JECHAC ABY DOTRZEC NA PIETRO int==w Z UWZGLEDNIENIEM direction I INNYCH POLECEN DANEJ WINDY
        int dystans(int w, char direction);






//AKTUALIZACJA DANYCH WINDY
        void aktualizuj(int i);

};



bool czy_jedzie(int numerwindy, int numerpietra);


void wywolaj_winde(int numer_windy, int w, char direction);

