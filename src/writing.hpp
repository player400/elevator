#pragma once

class Writing
{
    private:

        string character_list = " ! #$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[/]^_`abcdefghijklmnopqrstuvwxyz{|}~";

        float u_chunk=0.0625;
        float v_chunk=0.1667;

        Buffer buffer;
        Texture font;

        enum pos_
        {
            CENTER,
            LEFT,
        };

        pos_ pos;

        float height, width, margin_top, margin_left;

        float vertical_position;

        int jaki_numer_znaku(char character);

        int kolumna(char character);

        int wiersz(char character);

        float wartosc_u1(int kolumna);

        float wartosc_v1(int wiersz);

        float wartosc_u2(int kolumna);

        float wartosc_v2(int wiersz);

        void wyswietl(float u1, float v1, float u2, float v2, float x1, float y1, float x2, float y2);

        void napisz_znak(char character, float x1, float y1, float x2, float y2);

    public:

        void kolejna_linia();

        void rysuj();

        void zmien_pozycjonowanie();

        void zmien_margines(float new_margin);

        void zmien_rozmiar(float new_height, float new_width);


        void pisz(string text);


        Writing(float height, float width, float vertical_position, string font_file_texture);

};


