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

        //METODA ZWRACA NAJNIZSZE PIÊTRO Z VECTORA polecenia
        int minimum();

        //METODA ZWRACA NAJWYZSZE PIÊTRO Z VECTORA polecenia
        int maksimum();

        //METODA DODAJE PIETRO w DO VECTORA polecenia
        void dodaj_polecenie(int w);

        //METODA DODAJE PIETRO w DO VECTORA przystanki
        void dodaj_przystanek(int w);

        //METODA WYPISUJE STATUS WINDY
        void wyswietl();

        //METODA WYWO£YWANA PRZEZ METODE aktualizuj W MOMENCIE GDY WINDA WJEZDZA NA PIÊTRO, METODA TA MIN. SPRAWDZA CZY WINDA POWINNA SIÊ ZATRZYMAÆ
        void zmien_pietro();

    public:

        //METODA ZWRACA true JEŒLI WINDA JEST NA PIÊTRZE w ORAZ STOI
        bool czy_stoi(int w);

        //METODA ZWRACA true JESLI WINDA JEDZIE JUZ NA PIÊTRO w, ORAZ ZWRACA false JEŒLI NIE
        bool czy_jedzie(int w);

        //METODA DODAJ¥CA POLECENIE LUB PRZYSTANEK DLA WINDY
        void dodaj_komende(int w);

        //METODA OBLICZAJACA JAK DELAKO WINDA MUSIALABY JECHAC ABY DOTRZEC NA PIETRO w Z UWZGLEDNIENIEM direction I INNYCH POLECEN DANEJ WINDY
        int dystans(int w, char direction);

        //AKTUALIZACJA DANYCH WINDY
        void aktualizuj();

        //METODA-KONSTRUKTOR KTÓRA USTAWIA ID WINDY (ZMIENNA i)
        ElevatorData(int i);

};

//FUNKCJA ZWRACA NUMER WINDY JAD¥CEJ NA PIÊTRO w LUB ZWRACA -1 JEŒLI NA TO PIÊTRO NIE JEDZIE ¯ADNA WINDA.
//JEŒLI elevator_number==-1 TO SPRAWDZI WSZYSTKIE WINDY, W PRZECIWNYM WYPADKU TYLKO JEDNA
int czy_jedzie(int elevator_number, int numerpietra);

//FUNKCJA WYSY£A WINDÊ elevator_number NA PIÊTRO w, JEŒLI numer_windy==-1 TO WYSY£A NAJBLI¯SZ¥ WINDÊ (USTALANE ZA POMOC¥ METODY dystans W KLASIE ElevatorData)
//I ZWRACA NUMER WYS£ANEJ WINDY
int wywolaj_winde(int elevator_number, int w, char direction);

