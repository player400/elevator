#pragma once

class EntityData
{

    private:

        int destination;
        int origin;
        int elevator_number;
        int l;

        enum status_
        {
            WAITING,
            UNDERWAY,
        };

        status_ status;

        //METODA USTALAJ�CA KIERUNEK (u (UP) LUB d (DOWN) NA PODSTAWIE RӯNICY destination-origin, JESLI DIFFERENCE DODATNIE - u, JESLI DIFFERENCE UJEMNE - d
        char kierunek(int difference);

        //METODA WYPISUJ�CA STATUS PASA�ERA
        void wyswietl();

    public:

        //true - JE�ELI PASA�ER DOJECHA� DO destination, false - JE�LI NIE
        bool should_remove;

        //METODA - KONSTRUKTOR, USTAWIA WARTO�CI ZMIENNYCH, WZYWA WIND� DO origin
        EntityData(int orig, int dest, int id);

        //METODA WYKONUJ�CA SI� CO KLATK�, AKTUALIZUJE STATUS PASA�ERA, ZMIENIA should_remove NA TRUE JE�LI PASA�ER DOJECHA� I WYSY�A WIND� DO destination PO TYM JAK DOTRZE ONA DO origin
        void aktualizuj();

};
