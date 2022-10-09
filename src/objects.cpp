#include "utilities.hpp"
#include "objects.hpp"


Object& Object::utworz_okienko(TextureBuffer& texture_buffer_, Object* ref_pointer)
{
    return popup_windows.emplace_back(texture_buffer_, false, -0.6, ref_pointer);
}


void Object::aktywuj_okienko()
{
    is_popup_active=true;
}


void Object::dezaktywuj_okienko()
{
    is_popup_active=false;
}


bool Object::czy_wcisniety()
{
    if(left_mouse_state==1)
    {
//        czyszczenie();
//        cout<<x1<<" "<<cursor_x<<" "<<x2<<endl;
//        cout<<y2<<" "<<cursor_y<<" "<<y1<<endl;
//        exit(9);

        if(cursor_x>x1 && cursor_x<x2 && cursor_y<y1 && cursor_y>y2)
        {
            return true;
        }
    }
    return false;
}


void Object::inicjalizuj(pos_ pos, float margin_, float margin_top_, float width_, float height_)
{
    margin=margin_;
    margin_top=margin_top_;

    width=width_;
    height=height_;

    float ref_x1=reference_object_pointer -> x1;
    float ref_x2=reference_object_pointer -> x2;
    float ref_y1=reference_object_pointer -> y1;

    switch(pos)
    {
        case CENTER:
            {
                float middle=(ref_x1+ref_x2)/2.0;
                x1=middle-(width/2.0);
                x2=x1+width;
            }
            break;
        case LEFT:
            {
                x1=ref_x1+margin;
                x2=x1+width;
            }
            break;
        case RIGHT:
            {
                x2=ref_x2-margin;
                x1=x2-width;
            }
            break;
    }

    y1=ref_y1-margin_top;
    y2=y1-height;
}


void Object::rysuj()
{

    texturebuffer.ustaw_vertexy(x1, y1, x2, y2, z, 0, 0, 1, 1);

    for(auto& child_object : child_objects)
    {
        child_object.rysuj();
    }

    if(is_popup_active)
    {
        //popup_window(popup_windows);
        for(auto& popup_window : popup_windows)
        {
            popup_window.rysuj();
        }
    }

}


Object& Object::utworz_obiekt(TextureBuffer& texture_buffer_)
{
    return child_objects.emplace_back(texture_buffer_, false, z-0.1, this);
}


Writing& Object::utworz_tekst(float height, float width, float margin_top, TextureBuffer& texture_buffer_)
{
    return writings.emplace_back(this, z-0.1, height, width, margin_top, texture_buffer_);
}


void Object::nadpisz_z(float z_)
{
    z=z_;

    for(auto& child_object : child_objects)
    {
        child_object.nadpisz_z(z-0.1);
    }
}


Object::Object(TextureBuffer& texture_buffer_, bool is_first_object, float z_, Object* reference_object_pointer_):texturebuffer(texture_buffer_)
{
    if(is_first_object)
    {
        x1=-1;
        y1=1;
        x2=1;
        y2=-1;
    }
    else
    {
        z=z_;
        reference_object_pointer=reference_object_pointer_;
    }

}
