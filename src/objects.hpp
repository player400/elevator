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

    public:

        enum pos_
        {
            CENTER,
            LEFT,
            RIGHT,
        };

        float x1, y1, x2, y2;


        bool czy_wcisniety();


        void rysuj();


        void inicjalizuj(pos_ pos, float margin_, float margin_top_, float width_, float height_);


        Object& utworz_obiekt(TextureBuffer& texture_buffer_);


        Writing& utworz_tekst(float height, float width, float margin_top, TextureBuffer& texture_buffer_);


        Object(TextureBuffer& texture_buffer_, bool is_first_object, float z_index_, Object* reference_object_pointer);


        Object(const Object& object) = delete;

        ~Object() {
            cout << "~Object\n";
        }

        Object(Object&& object):child_objects(move(object.child_objects)), writings(move(object.writings)), texturebuffer(object.texturebuffer)
        {
            margin=object.margin;
            margin_top=object.margin_top;
            width=object.width;
            z=object.z;
            height=object.height;
            reference_object_pointer=object.reference_object_pointer;
            x1=object.x1;
            y1=object.y1;
            x2=object.x2;
            y2=object.y2;
        }

};


