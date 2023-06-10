#pragma once
#include "utilities.hpp"

class Object;

class Writing
{
    private:

        string character_list = " ! #$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[/]^_`abcdefghijklmnopqrstuvwxyz{|}~";

        float u_chunk=0.0625;
        float v_chunk=0.1667;

        TextureBuffer& texturebuffer;

        Object* reference_object_pointer;

        float z;

        enum pos_
        {
            CENTER,
            LEFT,
        };

        pos_ pos;

        struct letter_vertex
        {
            float u1;
            float v1;

            float u2;
            float v2;


            float x1;
            float y1;

            float x2;
            float y2;
        };

        vector<letter_vertex>verteksy;

        float height, width, margin_top, margin_left;

        float vertical_position;

        int jaki_numer_znaku(char character);

        int kolumna(char character);

        int wiersz(char character);

        float wartosc_u1(int kolumna);

        float wartosc_v1(int wiersz);

        float wartosc_u2(int kolumna);

        float wartosc_v2(int wiersz);

        void zapisz_verteks(float u1, float v1, float u2, float v2, float x1, float y1, float x2, float y2);

        void napisz_znak(char character, float x1, float y1, float x2, float y2);

    public:

        void kolejna_linia();

        void rysuj();

        void zmien_pozycjonowanie();

        void zmien_margines(float new_margin);

        void zmien_rozmiar(float new_height, float new_width);

        void nadpisz_z(float z_);


        void pisz(string text);


        void koniec();

        void inicjalizuj(float height_, float width_, float margin_top_);

        Writing(Object* reference_object_pointer_, float z_, TextureBuffer& texture_buffer_);


        Writing(const Writing& writing) = delete;


        Writing(Writing&& writing):texturebuffer(writing.texturebuffer), verteksy(move(writing.verteksy))
        {
            u_chunk=writing.u_chunk;
            v_chunk=writing.v_chunk;
            z=writing.z;
            character_list=writing.character_list;
            reference_object_pointer=writing.reference_object_pointer;
        }

};


