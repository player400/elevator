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

        //METODA USTALAJACA KIERUNEK (u (UP) LUB d (DOWN) NA PODSTAWIE RÓZNICY destination-origin, JESLI DIFFERENCE DODATNIE - u, JESLI DIFFERENCE UJEMNE - d
        char kierunek(int difference);

        //METODA WYPISUJ¥CA STATUS PASAZERA
        void wyswietl();

    public:

        //true - JEZELI PASAZER DOJECHA£ DO destination, false - JESLI NIE
        bool should_remove;

        //METODA - KONSTRUKTOR, USTAWIA WARTSŒCI ZMIENNYCH, WZYWA WINDE DO origin
        EntityData(int orig, int dest, int id);

        //METODA WYKONUJACA SIE CO KLATKE, AKTUALIZUJE STATUS PASAAERA, ZMIENIA should_remove NA TRUE JESLI PASAZER DOJECHAL I WYSYLA WINDE DO destination PO TYM JAK DOTRZE ONA DO origin
        void aktualizuj();

};
