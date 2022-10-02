#include "utilities.hpp"
#include "objects.hpp"


void Object::rysuj()
{


    buffer.vertex(x1, y1, z, 0, 0, 1, 0, 0);
    buffer.vertex(x2, y2, z, 0, 1, 0, 1, 1);
    buffer.vertex(x1, y2, z, 1, 0, 0, 0, 1);

    buffer.vertex(x1, y1, z, 0, 0, 1, 0, 0);
    buffer.vertex(x2, y1, z, 1, 0, 0, 1, 0);
    buffer.vertex(x2, y2, z, 0, 1, 0, 1, 1);

    buffer.wyslij();

    texture.bind();
    buffer.rysuj();
    //buffer.czysc();

    for(auto& child_object : child_objects)
    {
        child_object.rysuj();
    }

    for(auto& writing : writings)
    {
        writing.rysuj();
    }
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


Object& Object::utworz_obiekt(string texture_file_name)
{
    return child_objects.emplace_back(texture_file_name, false, z-0.1, this);
}


Writing& Object::utworz_tekst(float height, float width, float margin_top, string font_file_name)
{
    return writings.emplace_back(this, z-0.1, height, width, margin_top, font_file_name);
}


Object::Object(string texture_file_name, bool is_first_object, float z_, Object* reference_object_pointer_):texture(texture_file_name)
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
