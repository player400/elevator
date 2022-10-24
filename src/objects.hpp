#pragma once

#include "utilities.hpp"
#include "writing.hpp"

using namespace std;

class Object
{
    private:

        list<Object>child_objects;
        list<Writing>writings;

        TextureBuffer& texturebuffer;

        float margin=0;
        float margin_top=0;

        float width, height;

        Object* reference_object_pointer;

        float z;

        Writing* text_input_pointer;
        bool is_text_input_active=false;
        string text_input="";
        float text_height;
        float text_width;
        float text_margin;

        list<Object>popup_windows;


    public:
        bool is_popup_active=false;


        enum pos_
        {
            CENTER,
            LEFT,
            RIGHT,
        };

        float x1, y1, x2, y2;


        Object* utworz_okienko(TextureBuffer& texturebuffer, Object* ref_pointer);


        void aktywuj_okienko();


        void dezaktywuj_okienko();


        bool czy_wcisniety();


        void klawisz_wcisniety(int keycode);


        void utworz_pole_tekstowe(float height, float width, float margin_top, TextureBuffer& texture_buffer_);


        void aktywuj_pole_tekstowe();


        string dezaktywuj_pole_tekstowe();


        void inicjalizuj(pos_ pos, float margin_, float margin_top_, float width_, float height_);


        void rysuj();


        void usun_obiekt(Object* pointer);


        Object* utworz_obiekt(TextureBuffer& texture_buffer_);


        Writing* utworz_tekst(TextureBuffer& texture_buffer_);


        void nadpisz_z(float z_);


        Object(TextureBuffer& texture_buffer_, bool is_first_object, float z_index_, Object* reference_object_pointer);


        Object(const Object& object) = delete;

        ~Object() {
            //delete text_input_pointer;
        }

        Object(Object&& object):child_objects(move(object.child_objects)), writings(move(object.writings)), texturebuffer(object.texturebuffer), popup_windows(move(object.popup_windows))
        {
            margin=object.margin;
            margin_top=object.margin_top;

            width=object.width;
            z=object.z;
            height=object.height;

            reference_object_pointer=object.reference_object_pointer;
            is_popup_active=object.is_popup_active;

            text_input=object.text_input;
            is_text_input_active=object.is_text_input_active;
            text_input_pointer=object.text_input_pointer;
            text_height=object.text_height;
            text_width=object.text_width;
            text_margin=object.text_margin;

            x1=object.x1;
            y1=object.y1;
            x2=object.x2;
            y2=object.y2;
        }

};


