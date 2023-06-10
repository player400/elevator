#include "utilities.hpp"
#include "objects.hpp"


Object* Object::utworz_okienko(TextureBuffer& texture_buffer_, Object* ref_pointer)
{
    return &popup_windows.emplace_back(texture_buffer_, false, -0.6, ref_pointer);
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
        cout<<x1<<" "<<cursor_x<<" "<<x2<<endl;
        cout<<y2<<" "<<cursor_y<<" "<<y1<<endl;
//        exit(9);

        if(cursor_x>x1 && cursor_x<x2 && cursor_y<y1 && cursor_y>y2)
        {
            //exit(89);
            return true;
        }
    }
    return false;
}


void Object::klawisz_wcisniety(int keycode)
{
    if(is_text_input_active)
    {
        if(keycode==WXK_BACK)
        {
            if(text_input.size()>0)
            {
                text_input.pop_back();
            }
        }
        else if(keycode>=48 && keycode <=57)
        {
            text_input.push_back(char(keycode));
        }
    }


    for(auto& child_object : child_objects)
    {
        child_object.klawisz_wcisniety(keycode);
    }

    for(auto& popup_window : popup_windows)
    {
        popup_window.klawisz_wcisniety(keycode);
    }
}


void Object::utworz_pole_tekstowe(float height, float width, float margin_top, TextureBuffer& texture_buffer_)
{
    text_height=height;
    text_width=width;
    text_margin=margin_top;

    if(text_input_pointer==nullptr)
    {
        text_input_pointer = new Writing(this, z-0.1, texture_buffer_);
    }
}


void Object::aktywuj_pole_tekstowe()
{
    is_text_input_active=true;
}


string Object::dezaktywuj_pole_tekstowe()
{
    is_text_input_active=false;
    return text_input;
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
    //cout<<ref_x1<<" "<<ref_x2<<" "<<reference_object_pointer<<endl;
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

    for(auto& writing : writings)
    {
        writing.rysuj();
    }


    if(is_popup_active)
    {
        for(auto& popup_window : popup_windows)
        {
            popup_window.rysuj();
        }
    }


    if(is_text_input_active)
    {
        if(time_since_logic_update<=0.5)
        {
            text_input=text_input+'_';
        }
        else
        {
            text_input=text_input+' ';
        }
    }



    if(text_input.size()>0)
    {
        text_input_pointer -> inicjalizuj(text_height, text_width, text_margin);
        text_input_pointer -> pisz(text_input);
        text_input_pointer -> koniec();
        text_input_pointer -> rysuj();
    }

    if(is_text_input_active)
    {
        text_input.pop_back();
    }

}

void Object::usun_obiekt(Object* pointer)
{
    //auto it=child_objects.begin();
    //child_objects.erase(it);
    child_objects.remove_if([=](Object& element){ bool flag = (&element == pointer); cout<<flag<<endl; return flag; });
    //exit(51);
}

Object* Object::utworz_obiekt(TextureBuffer& texture_buffer_)
{
    return &child_objects.emplace_back(texture_buffer_, false, z-0.1, this);
}


Writing* Object::utworz_tekst(TextureBuffer& texture_buffer_)
{
    return &writings.emplace_back(this, z-0.1, texture_buffer_);
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
        reference_object_pointer=reference_object_pointer_;
    }
    z=z_;
}
