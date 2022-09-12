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

        //METODA USTALAJ¥CA KIERUNEK (u (UP) LUB d (DOWN) NA PODSTAWIE RÓ¯NICY destination-origin, JESLI DIFFERENCE DODATNIE - u, JESLI DIFFERENCE UJEMNE - d
        char kierunek(int difference);

        //METODA WYPISUJ¥CA STATUS PASA¯ERA
        void wyswietl();

    public:

        //true - JE¯ELI PASA¯ER DOJECHA£ DO destination, false - JEŒLI NIE
        bool should_remove;

        //METODA - KONSTRUKTOR, USTAWIA WARTOŒCI ZMIENNYCH, WZYWA WINDÊ DO origin
        EntityData(int orig, int dest, int id);

        //METODA WYKONUJ¥CA SIÊ CO KLATKÊ, AKTUALIZUJE STATUS PASA¯ERA, ZMIENIA should_remove NA TRUE JEŒLI PASA¯ER DOJECHA£ I WYSY£A WINDÊ DO destination PO TYM JAK DOTRZE ONA DO origin
        void aktualizuj();

};
