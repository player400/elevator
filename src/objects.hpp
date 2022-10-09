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

        list<Object>popup_windows;
        bool is_popup_active=false;

    public:



        enum pos_
        {
            CENTER,
            LEFT,
            RIGHT,
        };

        float x1, y1, x2, y2;


        Object& utworz_okienko(TextureBuffer& texturebuffer, Object* ref_pointer);


        void aktywuj_okienko();


        void dezaktywuj_okienko();


        bool czy_wcisniety();


        void inicjalizuj(pos_ pos, float margin_, float margin_top_, float width_, float height_);


        void rysuj();


        Object& utworz_obiekt(TextureBuffer& texture_buffer_);


        Writing& utworz_tekst(float height, float width, float margin_top, TextureBuffer& texture_buffer_);


        void nadpisz_z(float z_);


        Object(TextureBuffer& texture_buffer_, bool is_first_object, float z_index_, Object* reference_object_pointer);


        Object(const Object& object) = delete;

        ~Object() {
            cout << "~Object\n";
        }

        Object(Object&& object):child_objects(move(object.child_objects)), writings(move(object.writings)), popup_windows(move(object.popup_windows)),texturebuffer(object.texturebuffer)
        {
            margin=object.margin;
            margin_top=object.margin_top;
            width=object.width;
            z=object.z;
            height=object.height;
            reference_object_pointer=object.reference_object_pointer;
            is_popup_active=object.is_popup_active;
            x1=object.x1;
            y1=object.y1;
            x2=object.x2;
            y2=object.y2;
        }

};


