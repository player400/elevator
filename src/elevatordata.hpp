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
        int i;

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

        //METODA ZWRACA NAJNIZSZE PI�TRO Z VECTORA polecenia
        int minimum();

        //METODA ZWRACA NAJWYZSZE PI�TRO Z VECTORA polecenia
        int maksimum();

        //METODA DODAJE PIETRO w DO VECTORA polecenia
        void dodaj_polecenie(int w);

        //METODA DODAJE PIETRO w DO VECTORA przystanki
        void dodaj_przystanek(int w);

        //METODA WYPISUJE STATUS WINDY
        void wyswietl();

        //METODA WYWO�YWANA PRZEZ METODE aktualizuj W MOMENCIE GDY WINDA WJEZDZA NA PI�TRO, METODA TA MIN. SPRAWDZA CZY WINDA POWINNA SI� ZATRZYMA�
        void zmien_pietro();

    public:

        //METODA ZWRACA true JE�LI WINDA JEST NA PI�TRZE w ORAZ STOI
        bool czy_stoi(int w);

        //METODA ZWRACA true JESLI WINDA JEDZIE JUZ NA PI�TRO w, ORAZ ZWRACA false JE�LI NIE
        bool czy_jedzie(int w);

        //METODA DODAJ�CA POLECENIE LUB PRZYSTANEK DLA WINDY
        void dodaj_komende(int w);

        //METODA OBLICZAJACA JAK DELAKO WINDA MUSIALABY JECHAC ABY DOTRZEC NA PIETRO w Z UWZGLEDNIENIEM direction I INNYCH POLECEN DANEJ WINDY
        int dystans(int w, char direction);

        //AKTUALIZACJA DANYCH WINDY
        void aktualizuj();

        //METODA-KONSTRUKTOR KT�RA USTAWIA ID WINDY (ZMIENNA i)
        ElevatorData(int i);

};

//FUNKCJA ZWRACA NUMER WINDY JAD�CEJ NA PI�TRO w LUB ZWRACA -1 JE�LI NA TO PI�TRO NIE JEDZIE �ADNA WINDA.
//JE�LI elevator_number==-1 TO SPRAWDZI WSZYSTKIE WINDY, W PRZECIWNYM WYPADKU TYLKO JEDNA
int czy_jedzie(int elevator_number, int numerpietra);

//FUNKCJA WYSY�A WIND� elevator_number NA PI�TRO w, JE�LI numer_windy==-1 TO WYSY�A NAJBLI�SZ� WIND� (USTALANE ZA POMOC� METODY dystans W KLASIE ElevatorData)
//I ZWRACA NUMER WYS�ANEJ WINDY
int wywolaj_winde(int elevator_number, int w, char direction);

