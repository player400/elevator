#include "utilities.hpp"
#include "writing.hpp"
#include "objects.hpp"

using namespace std;

int Writing::jaki_numer_znaku(char character)
{
    for(int i=0; i<95; i++)
    {
        if(character==character_list[i])
        {
            return i;
        }
    }

    czyszczenie();
    cout<<"ERROR: CHARACTER NOT RECOGNISED";
    exit(45);
}

int Writing::kolumna(char character)
{
    return jaki_numer_znaku(character)%16;
}

int Writing::wiersz(char character)
{
    return jaki_numer_znaku(character)/16;
}

float Writing::wartosc_u1(int kolumna)
{
    return kolumna*u_chunk;
}

float Writing::wartosc_v1(int wiersz)
{
    return wiersz*v_chunk+0.01;
}

float Writing::wartosc_u2(int kolumna)
{
    return wartosc_u1(kolumna)+(u_chunk/2);
}

float Writing::wartosc_v2(int wiersz)
{
    return wartosc_v1(wiersz)+v_chunk-0.01;
}

void Writing::zapisz_verteks(float u1, float v1, float u2, float v2, float x1, float y1, float x2, float y2)
{
    letter_vertex vertex;

    vertex.u1=u1;
    vertex.v1=v1;

    vertex.u2=u2;
    vertex.v2=v2;


    vertex.x1=x1;
    vertex.y1=y1;

    vertex.x2=x2;
    vertex.y2=y2;

    verteksy.push_back(vertex);
}

void Writing::napisz_znak(char character, float x1, float y1, float x2, float y2)
{
    int column = kolumna(character);
    int row = wiersz(character);
    zapisz_verteks(wartosc_u1(column), wartosc_v1(row), wartosc_u2(column), wartosc_v2(row), x1, y1, x2, y2);
}

void Writing::kolejna_linia()
{
    vertical_position=vertical_position+height;
}

void Writing::rysuj()
{
    for(auto& verteks : verteksy)
    {
         texturebuffer.ustaw_vertexy(verteks.x1, verteks.y1, verteks.x2, verteks.y2, z, verteks.u1, verteks.v1, verteks.u2, verteks.v2);
    }

    verteksy.clear();
}

void Writing::nadpisz_z(float z_)
{
    z=z_;
}

void Writing::pisz(string text)
{
    float ref_x1=reference_object_pointer->x1;
    float ref_x2=reference_object_pointer->x2;
    float ref_y1=reference_object_pointer->y1;

    float horizontal_position;

    if(pos==CENTER)
    {
        float middle=(ref_x1+ref_x2)/2.0;
        horizontal_position=middle-(text.size()*width*0.5);
    }
    if(pos==LEFT)
    {
        horizontal_position=ref_x1+margin_left;
    }


    float y1=ref_y1-(margin_top+vertical_position);
    float y2=y1-height;


    for(int i=0; i<text.size(); i++)
    {
        float x1=horizontal_position+width*i;
        float x2=x1+width;
        napisz_znak(text[i], x1, y1, x2, y2);
    }



    kolejna_linia();
}

void Writing::zmien_pozycjonowanie()
{
    if(pos==CENTER)
    {
        pos=LEFT;
    }
    else
    {
        pos=CENTER;
    }
}

void Writing::zmien_margines(float new_margin)
{
    margin_left=new_margin;
}

void Writing::zmien_rozmiar(float new_height, float new_width)
{
    height=new_height;
    width=new_width;
}


void Writing::koniec()
{
    vertical_position=0;
    pos=CENTER;
}


void Writing::inicjalizuj(float height_, float width_, float margin_top_)
{
    height=height_;
    width=width_;
    margin_top=margin_top_;
}


Writing::Writing(Object* reference_object_pointer_, float z_, TextureBuffer& texture_buffer_):texturebuffer(texture_buffer_)
{
    vertical_position=0;

    margin_left=0;

    pos=CENTER;

    reference_object_pointer=reference_object_pointer_;
    z=z_;
}

