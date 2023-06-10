//EURO ELEVATOR Simulator Licence Agreement:
//
//COPYRIGHT (c) 2022 player400
//
//PLEASE FOLLOW THE FOLLOWING RULES WHILE USING, SHARING, DISTRIBUTING, CHANGING ETC. MY CODE:
//1. F*CK YOU THIEF, GO WRITE YOUR OWN CODE
//2. YOU CANT? GO CRY TO YOUR MOMMY
//3. JUST JOKING, GO TO pasjainformatyki.pl AND LEARN TO MAKE NOT-SO-COOL SOFTWARE YOURSELF!
//4. But actually idc I'd need to be a moron to write a licence for few hundred lines of code and legal stuff is boring anyway - just do whatever you want with it
//5. HAVE FUN :-)
//6. PS - I am not responsible for anything anyone uses my software for. If it breaks down your machine (higly unlikely), it's your problem. I do not guarantee anything concerning this code.

#define NBI_LIB_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "utilities.hpp"
#include "objects.hpp"

volatile bool wstrzymywanie;

bool was_window_resized=false;




void glowna_petla();

int menu();

int wybor_ilosci_wind();

void sterowanie();

void otworz_okno(int width, int height);

void utworz_program();

void uruchom_opengl();

void sigsegv_notice(int sig_num) {
 std::cout << "SIGSEGV!" << std::endl << std::flush;
 exit(6);
}


int main()
{
    thread t1(sterowanie);
    wstrzymywanie=false;
    //signal(SIGSEGV, sigsegv_notice);


    otworz_okno(1500, 900);
    utworz_program();
    uruchom_opengl();

while(true)
{
    int modenumber=menu();

    ile_wind=wybor_ilosci_wind();

    if(ile_wind>0)
    {
        break;
    }
}

    //ile_wind=2;

    for(int i=0;i<ile_wind;i++)
    {
        ElevatorData pustawinda(i);
        windy.push_back(pustawinda);
    }

    glowna_petla();


    return 0;
}


void glowna_petla()
{
    double timer = winxGetTime();

    TextureBuffer white("white.png");
    TextureBuffer black("black.png");
    TextureBuffer white_font("white_font.png");
    TextureBuffer black_font("black_font.png");
    TextureBuffer up("up.png");
    TextureBuffer down("down.png");

    basic = new Object(black, true, 0, nullptr);

    const float relative_list_width=1.4;

    Object* menu = basic->utworz_obiekt(white);
        Object* call_buttons = menu->utworz_obiekt(black);
            Writing* call_caption = call_buttons->utworz_tekst(white_font);
            Object* call_up = call_buttons->utworz_obiekt(up);
            Object* call_down = call_buttons->utworz_obiekt(down);
            Object* call_elevator_window = call_buttons->utworz_okienko(white, basic);
                Writing* call_elevator_window_text = call_elevator_window->utworz_tekst(black_font);
                Object* call_elevator_textbox = call_elevator_window->utworz_obiekt(black);
                Writing* call_elevator_window_text2 = call_elevator_window->utworz_tekst(black_font);
                Object* call_elevator_button_container = call_elevator_window->utworz_obiekt(black);
                    Object* call_back = call_elevator_button_container->utworz_obiekt(up);
                    Object* call_confirm = call_elevator_button_container->utworz_obiekt(down);


        Object* passenger_list = menu->utworz_obiekt(black);
            Object* create_passenger_button = passenger_list->utworz_obiekt(white);
                Writing* create_passenger_button_caption = create_passenger_button->utworz_tekst(black_font);
                Object* passenger_creating_window = create_passenger_button->utworz_okienko(white, basic);
                    Writing* passenger_creating_window_text1 = passenger_creating_window->utworz_tekst(black_font);
                    Object* passenger_textbox1 = passenger_creating_window->utworz_obiekt(black);
                    Writing* passenger_creating_window_text2 = passenger_creating_window->utworz_tekst(black_font);
                    Object* passenger_textbox2 = passenger_creating_window->utworz_obiekt(black);
                    Object* passenger_button_container = passenger_creating_window->utworz_obiekt(black);
                        Object* passenger_back = passenger_button_container->utworz_obiekt(up);
                        Object* passenger_confirm = passenger_button_container->utworz_obiekt(down);

            Writing* passenger_list_caption = passenger_list->utworz_tekst(white_font);

            vector<Object*>passengers;
                vector<Writing*>passenger_number;
                vector<Writing*>passenger_description;


    Object* elevator_list = basic->utworz_obiekt(black);
        Object* send_elevator_window = elevator_list->utworz_okienko(white, basic);
            Writing* send_elevator_window_text = send_elevator_window->utworz_tekst(black_font);
            Object* send_elevator_textbox = send_elevator_window->utworz_obiekt(black);
            Object* send_elevator_button_container = send_elevator_window->utworz_obiekt(black);
                Object* send_back = send_elevator_button_container->utworz_obiekt(up);
                Object* send_confirm = send_elevator_button_container->utworz_obiekt(down);
        Writing* elevator_list_caption = elevator_list->utworz_tekst(white_font);

        Object* elevators[ile_wind];
            Object* elevator_inside_box[ile_wind];
                Writing* elevator_number[ile_wind];
                Writing* floor_number[ile_wind];
                Object* direction_up[ile_wind];
                Object* direction_down[ile_wind];
                Writing* elevator_status[ile_wind];

        for(int i=0; i<ile_wind; i++)
        {
            elevators[i] = elevator_list->utworz_obiekt(white);
                elevator_inside_box[i] = elevators[i]->utworz_obiekt(black);
                    elevator_number[i] = elevator_inside_box[i]->utworz_tekst(white_font);
                    floor_number[i] = elevator_inside_box[i]->utworz_tekst(white_font);
                    direction_up[i] = elevator_inside_box[i]->utworz_okienko(up, elevator_inside_box[i]);
                    direction_down[i] = elevators[i]->utworz_okienko(down, elevator_inside_box[i]);
                    elevator_status[i] = elevator_inside_box[i]->utworz_tekst(white_font);
        }



    wstrzymywanie=false;

    bool lock_main_screen=false;
        bool create_passenger_window_active=false;
        bool send_elevator_window_active=false;
            int selected_elevator=0;
        bool call_elevator_window_active=false;
            char direction = 'u';

    while(true)
    {


        double now=winxGetTime();
        time_since_logic_update=now-timer;
        if(time_since_logic_update>1&&wstrzymywanie==false)
        {
            //czyszczenie();

            for(auto& winda : windy)
            {
                winda.aktualizuj();
            }

            for(int l=0; l<ile_bytow; l++)
            {
                byty[l].aktualizuj();
                if(byty[l].should_remove==true)
                {
                    passenger_list->usun_obiekt(passengers[l]);
                    passengers.erase(passengers.begin()+l);
                        passenger_number.erase(passenger_number.begin()+l);
                        passenger_description.erase(passenger_description.begin()+l);
                    ile_bytow--;
                }
            }

            byty.erase(std::remove_if(byty.begin(), byty.end(), [] (EntityData& byt) -> bool { return byt.should_remove; }), byty.end());
            timer=now;
        }


        if(passengers.size()<ile_bytow)
        {
            passengers.push_back(passenger_list->utworz_obiekt(black));
            int x=passengers.size()-1;
                passenger_number.push_back(passengers[x]->utworz_tekst(white_font));
                passenger_description.push_back(passengers[x]->utworz_tekst(white_font));
        }

        //cout<<passengers.size()<<endl;
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        menu->inicjalizuj(Object::RIGHT, 0, 0, 2-relative_list_width-szerokosc_bezwzgledna(50), 2);
            call_buttons->inicjalizuj(Object::CENTER, 0, 0.1 , 0.5, wysokosc_bezwzgledna(0.1*window_width+140));
                call_caption->inicjalizuj(wysokosc_bezwzgledna(60), szerokosc_bezwzgledna(36), wysokosc_bezwzgledna(20));
                call_caption->pisz("Call an elevator:");
                call_caption->koniec();
                call_down->inicjalizuj(Object::LEFT, szerokosc_bezwzgledna(0.1*window_width), wysokosc_bezwzgledna(110), szerokosc_bezwzgledna(0.1*window_width), wysokosc_bezwzgledna(0.1*window_width));
                call_up->inicjalizuj(Object::RIGHT, szerokosc_bezwzgledna(0.1*window_width), wysokosc_bezwzgledna(110), szerokosc_bezwzgledna(0.1*window_width), wysokosc_bezwzgledna(0.1*window_width));
                call_elevator_window->inicjalizuj(Object::CENTER, 0.75, 0.5, 0.5, 1);
                    call_elevator_window_text->inicjalizuj(wysokosc_bezwzgledna(60), szerokosc_bezwzgledna(36), wysokosc_bezwzgledna(100));
                    call_elevator_window_text->pisz("Elevator to floor:");
                    call_elevator_window_text->koniec();
                    call_elevator_textbox->inicjalizuj(Object::CENTER, 0, wysokosc_bezwzgledna(200), 0.4, wysokosc_bezwzgledna(100));
                        call_elevator_textbox->utworz_pole_tekstowe(wysokosc_bezwzgledna(60), szerokosc_bezwzgledna(36), wysokosc_bezwzgledna(20), white_font);
                    call_elevator_window_text2->inicjalizuj(wysokosc_bezwzgledna(60), szerokosc_bezwzgledna(36), wysokosc_bezwzgledna(400));
                    call_elevator_window_text2->pisz("From there it");
                    call_elevator_window_text2->pisz("will be going:");
                    call_elevator_window_text2->zmien_rozmiar(wysokosc_bezwzgledna(70), szerokosc_bezwzgledna(42));
                    call_elevator_window_text2->pisz(direction=='u' ? "UP" : "DOWN");
                    call_elevator_window_text2->koniec();
                    call_elevator_button_container->inicjalizuj(Object::CENTER, 0, 1-wysokosc_bezwzgledna(240), szerokosc_bezwzgledna(100), wysokosc_bezwzgledna(200));
                        call_back->inicjalizuj(Object::CENTER, 0, wysokosc_bezwzgledna(20), szerokosc_bezwzgledna(70), wysokosc_bezwzgledna(70));
                        call_confirm->inicjalizuj(Object::CENTER, 0, wysokosc_bezwzgledna(110), szerokosc_bezwzgledna(70), wysokosc_bezwzgledna(70));
            passenger_list->inicjalizuj(Object::CENTER, 0.1, 1.9-wysokosc_bezwzgledna(980), 0.5, wysokosc_bezwzgledna(980));
                create_passenger_button->inicjalizuj(Object::CENTER, szerokosc_bezwzgledna(10), wysokosc_bezwzgledna(880), 0.5-szerokosc_bezwzgledna(20), wysokosc_bezwzgledna(90));
                    passenger_creating_window->inicjalizuj(Object::CENTER, 0.75, 0.5, 0.5, 1);
                        passenger_creating_window_text1->inicjalizuj(wysokosc_bezwzgledna(60), szerokosc_bezwzgledna(36), wysokosc_bezwzgledna(100));
                        passenger_creating_window_text1->pisz("Going from:");
                        passenger_creating_window_text1->koniec();
                        passenger_textbox1->inicjalizuj(Object::CENTER, 0, wysokosc_bezwzgledna(200), 0.4, wysokosc_bezwzgledna(100));
                            passenger_textbox1->utworz_pole_tekstowe(wysokosc_bezwzgledna(60), szerokosc_bezwzgledna(36), wysokosc_bezwzgledna(20), white_font);
                        passenger_creating_window_text2->inicjalizuj(wysokosc_bezwzgledna(60), szerokosc_bezwzgledna(36), wysokosc_bezwzgledna(400));
                        passenger_creating_window_text2->pisz("to:");
                        passenger_creating_window_text2->koniec();
                        passenger_textbox2->inicjalizuj(Object::CENTER, 0, wysokosc_bezwzgledna(500), 0.4, wysokosc_bezwzgledna(100));
                            passenger_textbox2->utworz_pole_tekstowe(wysokosc_bezwzgledna(60), szerokosc_bezwzgledna(36), wysokosc_bezwzgledna(20), white_font);
                        passenger_button_container->inicjalizuj(Object::CENTER, 0, 1-wysokosc_bezwzgledna(240), szerokosc_bezwzgledna(100), wysokosc_bezwzgledna(200));
                            passenger_back->inicjalizuj(Object::CENTER, 0, wysokosc_bezwzgledna(20), szerokosc_bezwzgledna(70), wysokosc_bezwzgledna(70));
                            passenger_confirm->inicjalizuj(Object::CENTER, 0, wysokosc_bezwzgledna(110), szerokosc_bezwzgledna(70), wysokosc_bezwzgledna(70));
                    create_passenger_button_caption->inicjalizuj(wysokosc_bezwzgledna(60), szerokosc_bezwzgledna(36), wysokosc_bezwzgledna(15));
                    create_passenger_button_caption->pisz("Create Passenger");
                    create_passenger_button_caption->koniec();
                passenger_list_caption->inicjalizuj(wysokosc_bezwzgledna(60), szerokosc_bezwzgledna(36), wysokosc_bezwzgledna(20));
                passenger_list_caption->pisz("Passengers:");
                passenger_list_caption->koniec();

        int passenger_margin_top=80;

        for(int i=0; i<passengers.size(); i++)
        {
            passengers[i]->inicjalizuj(Object::CENTER, 0, wysokosc_bezwzgledna(passenger_margin_top+80*i+5), 0.5, wysokosc_bezwzgledna(80));
                passenger_number[i]->inicjalizuj(wysokosc_bezwzgledna(80), szerokosc_bezwzgledna(48), wysokosc_bezwzgledna(0));
                passenger_number[i]->zmien_pozycjonowanie();
                passenger_number[i]->pisz(to_string(byty[i].l));
                passenger_number[i]->koniec();

                passenger_description[i]->inicjalizuj(wysokosc_bezwzgledna(30), szerokosc_bezwzgledna(18), wysokosc_bezwzgledna(10));
                passenger_description[i]->zmien_pozycjonowanie();
                passenger_description[i]->zmien_margines(szerokosc_bezwzgledna(70));
                passenger_description[i]->pisz("Floor "+to_string(byty[i].origin)+" to floor "+to_string(byty[i].destination)+". Elevator: "+to_string(byty[i].elevator_number));
                if(byty[i].status==EntityData::UNDERWAY)
                {
                    passenger_description[i]->pisz("STATUS: ONBOARD THE ELEVATOR");
                }
                else if(time_since_logic_update<0.8)
                {
                    passenger_description[i]->pisz("STATUS: WAITING IN THE HALLWAY");
                }
                passenger_description[i]->koniec();
        }


        elevator_list->inicjalizuj(Object::LEFT, 0, 0, relative_list_width, 1.4);
            send_elevator_window->inicjalizuj(Object::CENTER, 0.75, 0.5, 0.5, 1);
                        send_elevator_window_text->inicjalizuj(wysokosc_bezwzgledna(60), szerokosc_bezwzgledna(36), wysokosc_bezwzgledna(100));
                        send_elevator_window_text->pisz("Elevator "+to_string(selected_elevator)+" to floor:");
                        send_elevator_window_text->koniec();
                        send_elevator_textbox->inicjalizuj(Object::CENTER, 0, wysokosc_bezwzgledna(200), 0.4, wysokosc_bezwzgledna(100));
                            send_elevator_textbox->utworz_pole_tekstowe(wysokosc_bezwzgledna(60), szerokosc_bezwzgledna(36), wysokosc_bezwzgledna(20), white_font);
                        send_elevator_button_container->inicjalizuj(Object::CENTER, 0, 1-wysokosc_bezwzgledna(240), szerokosc_bezwzgledna(100), wysokosc_bezwzgledna(200));
                            send_back->inicjalizuj(Object::CENTER, 0, wysokosc_bezwzgledna(20), szerokosc_bezwzgledna(70), wysokosc_bezwzgledna(70));
                            send_confirm->inicjalizuj(Object::CENTER, 0, wysokosc_bezwzgledna(110), szerokosc_bezwzgledna(70), wysokosc_bezwzgledna(70));
            elevator_list_caption->inicjalizuj(wysokosc_bezwzgledna(60), szerokosc_bezwzgledna(36), wysokosc_bezwzgledna(20));
            elevator_list_caption->pisz("Elevators:");
            elevator_list_caption->koniec();

        int elevator_counter=0;
        int elevator_margin_top=100;

        while(elevator_counter<ile_wind)
        {

            for(int margin_left=0; ; margin_left=margin_left+300)
            {
                if(elevator_counter>=ile_wind)
                {
                    break;
                }

                if(szerokosc_bezwzgledna(margin_left) > relative_list_width - szerokosc_bezwzgledna(300))
                {
                    break;
                }

                bool going_up=false;
                bool going_down=false;

                elevator_inside_box[elevator_counter]->dezaktywuj_okienko();
                elevators[elevator_counter]->dezaktywuj_okienko();

                if(windy[elevator_counter].status==ElevatorData::UP)
                {
                    going_up=true;
                }

                if(windy[elevator_counter].status==ElevatorData::DOWN)
                {
                    going_down=true;
                }

                elevators[elevator_counter]->inicjalizuj(Object::LEFT, szerokosc_bezwzgledna(50+margin_left), wysokosc_bezwzgledna(elevator_margin_top+50), szerokosc_bezwzgledna(250), wysokosc_bezwzgledna(200));
                    elevator_inside_box[elevator_counter]->inicjalizuj(Object::CENTER, szerokosc_bezwzgledna(5), wysokosc_bezwzgledna(5), szerokosc_bezwzgledna(240), wysokosc_bezwzgledna(190));

                        auto number = elevator_number[elevator_counter];

                        number->inicjalizuj(wysokosc_bezwzgledna(50), szerokosc_bezwzgledna(30), wysokosc_bezwzgledna(5));
                        number->zmien_margines(szerokosc_bezwzgledna(5));
                        number->zmien_pozycjonowanie();
                        number->pisz(to_string(windy[elevator_counter].i));
                        number->koniec();

                        auto floor = floor_number[elevator_counter];

                        floor->inicjalizuj(wysokosc_bezwzgledna(100), szerokosc_bezwzgledna(60), wysokosc_bezwzgledna(65));
                        floor->pisz(to_string(windy[elevator_counter].last_floor_number));
                        floor->koniec();

                        string st="";

                        if(windy[elevator_counter].status==ElevatorData::STOP)
                        {
                            if(time_since_logic_update<0.8)
                            {
                                st="DOOR OPEN";
                            }
                        }
                        else
                        {
                            for(int g=0; g<windy[elevator_counter].underway_status; g++)
                            {
                                st=st+".";
                            }
                        }

                        auto status = elevator_status[elevator_counter];

                        status->inicjalizuj(wysokosc_bezwzgledna(30), szerokosc_bezwzgledna(18), wysokosc_bezwzgledna(15));
                        status->zmien_pozycjonowanie();
                        if(windy[elevator_counter].status==ElevatorData::STOP)
                        {
                            status->zmien_margines(szerokosc_bezwzgledna(64));
                        }
                        else
                        {
                            status->zmien_margines(szerokosc_bezwzgledna(50));
                        }
                        status->pisz(st);
                        status->koniec();


                        direction_up[elevator_counter]->inicjalizuj(Object::RIGHT, szerokosc_bezwzgledna(10), wysokosc_bezwzgledna(10), szerokosc_bezwzgledna(40), wysokosc_bezwzgledna(40));
                        direction_down[elevator_counter]->inicjalizuj(Object::RIGHT, szerokosc_bezwzgledna(10), wysokosc_bezwzgledna(10), szerokosc_bezwzgledna(40), wysokosc_bezwzgledna(40));
                        direction_down[elevator_counter]->nadpisz_z(-0.4);
                        direction_up[elevator_counter]->nadpisz_z(-0.4);

                        if(going_up)
                        {
                            elevator_inside_box[elevator_counter]->aktywuj_okienko();
                        }
                        else if(going_down)
                        {
                            elevators[elevator_counter]->aktywuj_okienko();
                        }

                elevator_counter++;
            }

            elevator_margin_top=elevator_margin_top+250;
        }


        if(create_passenger_window_active)
        {
            if(passenger_confirm->czy_wcisniety() || enter_key_state&&(!passenger_textbox1->is_text_input_active))
            {
                string text1=passenger_textbox1->dezaktywuj_pole_tekstowe();
                string text2=passenger_textbox2->dezaktywuj_pole_tekstowe();

                int from;
                int to;

                if(text1.size()==0)
                {
                    from=0;
                }
                else
                {
                    from=napis_na_liczbe(text1);
                }

                if(text2.size()==0)
                {
                    to=0;
                }
                else
                {
                    to=napis_na_liczbe(text2);
                }

                int entity_number = 0;
                while(true)
                {
                    bool is_unique = true;
                    for(int l=0; l<ile_bytow; l++)
                    {
                        if(byty[l].l==entity_number)
                        {
                            is_unique=false;
                            entity_number++;
                        }
                    }
                    if(is_unique)
                    {
                        break;
                    }
                }
                EntityData pustybyt(from, to, entity_number);
                byty.push_back(pustybyt);
                ile_bytow++;

                create_passenger_window_active=false;
                lock_main_screen=false;
                create_passenger_button->dezaktywuj_okienko();
            }

            if(passenger_back->czy_wcisniety())
            {
                create_passenger_window_active=false;
                lock_main_screen=false;
                create_passenger_button->dezaktywuj_okienko();
            }

            if(passenger_textbox1->is_text_input_active)
            {
                if(enter_key_state)
                {
                        passenger_textbox2->aktywuj_pole_tekstowe();
                        passenger_textbox1->dezaktywuj_pole_tekstowe();
                }
            }

            if(passenger_textbox1->czy_wcisniety())
            {
                passenger_textbox1->aktywuj_pole_tekstowe();
                passenger_textbox2->dezaktywuj_pole_tekstowe();
            }

            if(passenger_textbox2->czy_wcisniety())
            {
                passenger_textbox2->aktywuj_pole_tekstowe();
                passenger_textbox1->dezaktywuj_pole_tekstowe();
            }
        }
        if(send_elevator_window_active)
        {
            if(send_confirm->czy_wcisniety() || enter_key_state)
            {
                string send_text=send_elevator_textbox->dezaktywuj_pole_tekstowe();
                elevator_list->dezaktywuj_okienko();
                lock_main_screen=false;
                send_elevator_window_active=false;
                wywolaj_winde(selected_elevator, napis_na_liczbe(send_text), 'u');
            }
            if(send_back->czy_wcisniety())
            {
                send_elevator_textbox->dezaktywuj_pole_tekstowe();
                elevator_list->dezaktywuj_okienko();
                lock_main_screen=false;
                send_elevator_window_active=false;
            }
        }
        if(call_elevator_window_active)
        {
            if(call_confirm->czy_wcisniety() || enter_key_state)
            {
                string call_text=call_elevator_textbox->dezaktywuj_pole_tekstowe();
                call_buttons->dezaktywuj_okienko();
                lock_main_screen=false;
                call_elevator_window_active=false;
                wywolaj_winde(-1, napis_na_liczbe(call_text), direction);
            }
            if(send_back->czy_wcisniety())
            {
                call_elevator_textbox->dezaktywuj_pole_tekstowe();
                call_buttons->dezaktywuj_okienko();
                lock_main_screen=false;
                call_elevator_window_active=false;
            }
        }
        if(!lock_main_screen)
        {
            if(create_passenger_button->czy_wcisniety())
            {
                create_passenger_button->aktywuj_okienko();
                create_passenger_window_active=true;
                lock_main_screen=true;
                passenger_textbox1->aktywuj_pole_tekstowe();
            }
            for(int i=0; i<ile_wind; i++)
            {
                if(elevators[i]->czy_wcisniety())
                {
                    elevator_list->aktywuj_okienko();
                    selected_elevator=i;
                    send_elevator_window_active=true;
                    lock_main_screen=true;
                    send_elevator_textbox->aktywuj_pole_tekstowe();
                }
            }
            if(call_up->czy_wcisniety())
            {
                    call_buttons->aktywuj_okienko();
                    direction='u';
                    call_elevator_window_active=true;
                    lock_main_screen=true;
                    call_elevator_textbox->aktywuj_pole_tekstowe();
            }
            if(call_down->czy_wcisniety())
            {
                    call_buttons->aktywuj_okienko();
                    direction='d';
                    call_elevator_window_active=true;
                    lock_main_screen=true;
                    call_elevator_textbox->aktywuj_pole_tekstowe();
            }
        }



        basic -> rysuj();

        black.rysuj();
        white.rysuj();
        white_font.rysuj();
        up.rysuj();
        down.rysuj();
        black_font.rysuj();


        winxSwapBuffers();
        winxPollEvents();

    }
}

int menu()
{
    TextureBuffer white_font("white_font.png");
    TextureBuffer black_font("black_font.png");
    TextureBuffer white("white.png");
    TextureBuffer black("black.png");
    TextureBuffer up("up.png");
    TextureBuffer down("down.png");

    basic=new Object(black, true, 0, nullptr);

    Writing* welcome_sign = basic->utworz_tekst(white_font);
    Object* menu_div = basic->utworz_obiekt(black);
        Object* sandbox_mode_button = menu_div->utworz_obiekt(white);
            Writing* sandbox_mode_button_text = sandbox_mode_button->utworz_tekst(black_font);
        Object* down_sign = menu_div->utworz_obiekt(down);
        Object* up_sign = menu_div->utworz_obiekt(up);



    while(true)
    {

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        welcome_sign->inicjalizuj(wysokosc_bezwzgledna(50), szerokosc_bezwzgledna(30), (1 - wysokosc_bezwzgledna(300))/2.0 - wysokosc_bezwzgledna(25));
        welcome_sign->pisz("Welcome to");
        welcome_sign->kolejna_linia();
        welcome_sign->zmien_rozmiar(wysokosc_bezwzgledna(100), szerokosc_bezwzgledna(60));
        welcome_sign->pisz("EURO ELEVATOR Simulator!");
        welcome_sign->zmien_rozmiar(wysokosc_bezwzgledna(25), szerokosc_bezwzgledna(15));
        welcome_sign->kolejna_linia();
        welcome_sign->pisz("Release 2.0");
        welcome_sign->koniec();


        menu_div->inicjalizuj(Object::CENTER, 0, 1 - wysokosc_bezwzgledna(50), 2, wysokosc_bezwzgledna(100));
            down_sign->inicjalizuj(Object::LEFT, 0, 0, szerokosc_bezwzgledna(100), wysokosc_bezwzgledna(100));
            up_sign->inicjalizuj(Object::RIGHT, 0, 0, szerokosc_bezwzgledna(100), wysokosc_bezwzgledna(100));

            sandbox_mode_button->inicjalizuj(Object::CENTER, 0, 0, szerokosc_bezwzgledna(700), wysokosc_bezwzgledna(100));
                sandbox_mode_button_text->inicjalizuj(wysokosc_bezwzgledna(50), szerokosc_bezwzgledna(30), wysokosc_bezwzgledna(25));
                sandbox_mode_button_text->pisz("SANDBOX MODE");
                sandbox_mode_button_text->koniec();



        if(sandbox_mode_button->czy_wcisniety())
        {
            return 1;
        }




        basic->rysuj();

        white_font.rysuj();
        black_font.rysuj();
        white.rysuj();
        black.rysuj();
        up.rysuj();
        down.rysuj();


        winxSwapBuffers();
		winxPollEvents();

    }

}


int wybor_ilosci_wind()
{

    string text_input="";

    TextureBuffer white_font("white_font.png");
    TextureBuffer black_font("black_font.png");
    TextureBuffer white("white.png");
    TextureBuffer black("black.png");
    TextureBuffer down("down.png");
    TextureBuffer up("up.png");

    basic = new Object(black, true, 0, nullptr);

    Writing* instruction = basic->utworz_tekst(white_font);
    Object* text_box = basic->utworz_obiekt(white);
    Object* start_button = basic->utworz_obiekt(down);
    Object* return_button = basic->utworz_obiekt(up);

    double timer=0;

    while(true)
    {
        double now=winxGetTime();
        time_since_logic_update=now-timer;
        if(time_since_logic_update>1&&wstrzymywanie==false)
        {
            timer=now;
        }
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        if(window_height>800)
        {
            instruction->inicjalizuj(wysokosc_bezwzgledna(50), szerokosc_bezwzgledna(30), wysokosc_bezwzgledna(400));
            instruction->pisz("SANDBOX MODE");
            instruction->kolejna_linia();
            instruction->zmien_margines(0.1);
            instruction->zmien_pozycjonowanie();
            instruction->zmien_rozmiar(wysokosc_bezwzgledna(30), szerokosc_bezwzgledna(18));
            instruction->pisz("To simulate calling an elevator from the hallway type: -1 <floor number> <direction>. Direction is either u - for going up or d - for going down.");
            instruction->pisz("This command will call the nearest elevator to the floor chosen.");
            instruction->kolejna_linia();
            instruction->pisz("To simulate sending a specific elevator somewhere using buttons in the elevator type: <elevator number> <floor number>.");
            instruction->kolejna_linia();
            instruction->kolejna_linia();
            instruction->pisz("Alternative way of controlling the elevators in the Sandbox Mode are Passengers.");
            instruction->kolejna_linia();
            instruction->pisz("Passenger is an entity simulating an actual person using the elevator. First it will summon one of the elevators to it's floor of origin.");
            instruction->pisz("As soon as the elevator arrives the passenger will automatically send it to the destination floor.");
            instruction->kolejna_linia();
            instruction->pisz("To create a new passenger type: -2 <floor of origin> <destination floor>");
            instruction->kolejna_linia();
            instruction->kolejna_linia();
            instruction->zmien_rozmiar(wysokosc_bezwzgledna(40), szerokosc_bezwzgledna(24));
            instruction->pisz("To start type the number of elevators you want to simulate and press Enter or click the white arrow below. Have fun!");
            instruction->zmien_rozmiar(wysokosc_bezwzgledna(25), szerokosc_bezwzgledna(15));
            instruction->pisz("Default elevator number is 2. If you type nothing and start, the simulation will launch with 2 elevators.");
            instruction->koniec();
        }

        return_button->inicjalizuj(Object::CENTER, 0, wysokosc_bezwzgledna(150), szerokosc_bezwzgledna(150), wysokosc_bezwzgledna(150));

        text_box->inicjalizuj(Object::CENTER, 0, 2 - wysokosc_bezwzgledna(600), 2, wysokosc_bezwzgledna(100));
            text_box->utworz_pole_tekstowe(wysokosc_bezwzgledna(60), szerokosc_bezwzgledna(33), wysokosc_bezwzgledna(20), black_font);

        start_button->inicjalizuj(Object::CENTER, 0, 2 - wysokosc_bezwzgledna(300), szerokosc_bezwzgledna(150), wysokosc_bezwzgledna(150));

        text_box->aktywuj_pole_tekstowe();


        if(start_button->czy_wcisniety() || enter_key_state)
        {
            string text=text_box->dezaktywuj_pole_tekstowe();

            return text.size() ? napis_na_liczbe(text) : 2;
        }


        if(return_button->czy_wcisniety())
        {
            return 0;
        }


        basic->rysuj();

        white_font.rysuj();
        black_font.rysuj();
        white.rysuj();
        black.rysuj();
        down.rysuj();
        up.rysuj();


        winxSwapBuffers();
		winxPollEvents();

    }
}


void sterowanie()
{
    while(true)
    {
        if(nbi_get_flag())
        {
            wstrzymywanie=true;
            int elevator_number;
            cin>>elevator_number;
            int w;
            cin>>w;

            if(elevator_number==-2)
            {
                int w2;
                cin>>w2;

                EntityData pustybyt(w, w2, ile_bytow);
                byty.push_back(pustybyt);
                ile_bytow++;

                wstrzymywanie=false;
                continue;
            }

            char direction='u';

            if(elevator_number==-1)
            {
                cin>>direction;
            }

            wywolaj_winde(elevator_number, w, direction);

            wstrzymywanie=false;
        }
    }
}


void otworz_okno(int width, int height)
{
    winxHint(WINX_HINT_OPENGL_MAJOR, 3);
    winxHint(WINX_HINT_OPENGL_MINOR, 3);
    winxHint(WINX_HINT_OPENGL_CORE, true);
    winxHint(WINX_HINT_VSYNC, WINX_VSYNC_ENABLED);

    window_width=width;
    window_height=height;

    if(!winxOpen(window_width, window_height, "EURO ELEVATOR Simulator / GuI / 2.0"))
    {
        czyszczenie();
		cout<<"magistermaks' library has failed you! Error code: "<< winxGetError();
		exit(1);
	}

	// use GLAD to load OpenGL functions
	gladLoadGL();

	winxSetCloseEventHandle([](){
        winxClose();
        exit(0);
    });

	winxSetResizeEventHandle([](int w, int h){
        was_window_resized=true;
        window_width=w;
        window_height=h;
        glViewport(0, 0, w, h);
    });

    winxSetKeybordEventHandle([](int state, int keycode){
        if(keycode==WXK_ENTER)
        {
            enter_key_state=state;
        }
        else if(state==1)
        {
            basic -> klawisz_wcisniety(keycode);
        }
    });

    winxSetCursorEventHandle([](int x, int y){
        czyszczenie();
//        cout<<window_width<<" "<<window_height<<endl;
//        cout<<x<<" "<<y<<endl;
        if(!was_window_resized)
        {
        y=y+((float)y/(window_height-42))*42;
        x=x+((float)x/(window_width-17))*17;
        }
//        cout<<x<<" "<<y<<endl;
        x=x-window_width/2;
        y=y-window_height/2;
        y=y*(-1);
//        cout<<x<<" "<<y<<endl;
        cursor_x=szerokosc_bezwzgledna(x)*2;
        cursor_y=wysokosc_bezwzgledna(y)*2;


//        cout<<cursor_x<<" "<<cursor_y<<endl;
    });

    winxSetButtonEventHandle([](int state, int button){
        if(button==WXB_LEFT)
        {
            left_mouse_state=state;
        }
    });
}


void utworz_program()
{
    program = new ShaderProgram(
        R"(
            #version 330 core
            layout (location = 0) in vec3 xyz;
            layout (location = 1) in vec3 rgb;
            layout (location = 2) in vec2 uv;
            out vec3 color;
            out vec2 cords;
            void main()
            {
                gl_Position = vec4(xyz.x, xyz.y, xyz.z, 1);
                cords = uv;
                color = rgb;
            }
        )",

        R"(
            #version 330 core
            uniform sampler2D test;
            in vec3 color;
            in vec2 cords;
            out vec4 frag;
            void main()
            {
                frag = texture(test, cords);
            }

        )"
    );

    program->uzyj();
}


void uruchom_opengl()
{
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glCullFace(GL_FRONT);
    glClearColor(0, 0, 0, 1);
}

