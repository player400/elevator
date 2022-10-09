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

volatile bool wstrzymywanie=false;

int menu(ShaderProgram& program);

int wybor_ilosci_wind(ShaderProgram& program);

void sterowanie();

int main()
{

//    cout<<"Welcome to EURO ELEVATOR Simulator 2.0 - PASSENGER UPDATE!"<<endl;
//    cout<<"Press 1 to launch the Sandbox Mode"<<endl;
    int modenumber=0;
//    char menu=nbi_std_input();
//    switch (menu)
//    {
//        case '1': {cout<<"Welcome to Sandbox Mode!"<<endl<<endl;modenumber=1;} break;
//    }
//    czyszczenie();
//
//
//    cout<<"CONTROLS:"<<endl<<endl;
//    cout<<"To simulate calling an elevator from the hallway type: -1 <floor number> <direction>. Direction is either u - for going up or d - for going down."<<endl;
//    cout<<"This command will call the nearest elevator to the floor chosen."<<endl<<endl;
//    cout<<"To simulate sending a specific elevator somewhere using buttons in the elevator type: <elevator number> <floor number>."<<endl<<endl;
//    cout<<"Alternative way of controlling the elevators are Passengers."<<endl;
//    cout<<"Passenger is an entity simulating an actual person going somewhere. First it will summon one of the elevators to it's floor of origin."<<endl;
//    cout<<"As soon as the elevator arrives the passenger will automatically send it to the destination floor."<<endl;
//    cout<<"To create a new passenger type: -2 <floor of origin> <destination floor>"<<endl<<endl;
//    cout<<"To start type the number of elevators you want to simulate and click Enter. Have fun!"<<endl;
//
//    cin>>ile_wind;


    czyszczenie();

    thread t1(sterowanie);

    wstrzymywanie=false;

    winxHint(WINX_HINT_OPENGL_MAJOR, 3);
    winxHint(WINX_HINT_OPENGL_MINOR, 3);
    winxHint(WINX_HINT_OPENGL_CORE, true);
    winxHint(WINX_HINT_VSYNC, WINX_VSYNC_ENABLED);

    window_width=1500;
    window_height=900;

    if(!winxOpen(window_width, window_height, "EURO ELEVATOR Simulator / GuI / 2.0"))
    {
        czyszczenie();
		cout<<"magistermaks' library has failed you! Error code: "<< winxGetError();
		return 1;
	}

	// use GLAD to load OpenGL functions
	gladLoadGL();

	winxSetCloseEventHandle([](){
        winxClose();
        exit(0);
    });

	winxSetResizeEventHandle([](int w, int h){
        window_width=w;
        window_height=h;
        glViewport(0, 0, w, h);
    });

    winxSetKeybordEventHandle([](int state, int keycode){
        if(keycode==WXK_ENTER)
        {
            enter_key_state=state;
        }
        if(keycode==WXK_BACK)
        {

            backspace_key_state=state;

        }
        else
        {
            keycode=keycode-48;
            number_keys_state[keycode]=state;
        }
    });

    winxSetCursorEventHandle([](int x, int y){
        y=y+((float)y/(window_height-42))*42;
        x=x+((float)x/(window_width-17))*17;
        czyszczenie();
        //cout<<x<<" "<<y<<endl;
        x=x-window_width/2;
        y=y-window_height/2;
        y=y*(-1);
        cursor_x=szerokosc_bezwzgledna(x)*2;
        cursor_y=wysokosc_bezwzgledna(y)*2;
    });

    winxSetButtonEventHandle([](int state, int button){
        if(button==WXB_LEFT)
        {
            left_mouse_state=state;
        }
    });



    ShaderProgram program(
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


    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glCullFace(GL_FRONT);
    glClearColor(0, 0, 0, 1);


    modenumber=menu(program);

    ile_wind=wybor_ilosci_wind(program);


    for(int i=0;i<ile_wind;i++)
    {
        ElevatorData pustawinda(i);
        windy.push_back(pustawinda);
    }


    double timer = winxGetTime();


    while(true)
    {

        double now=winxGetTime();
        if(now-timer>1&&wstrzymywanie==false)
        {
            czyszczenie();

            for(auto& winda : windy)
            {

                winda.aktualizuj();

            }

            for(auto& byt : byty)
            {
                byt.aktualizuj();
            }

            byty.erase(std::remove_if(byty.begin(), byty.end(), [] (EntityData& byt) -> bool { return byt.should_remove; }), byty.end());
            timer=now;
        }


        glClear(GL_COLOR_BUFFER_BIT);
        program.uzyj();


        winxSwapBuffers();
		winxPollEvents();
    }
    return 0;
}


int menu(ShaderProgram& program)
{

    TextureBuffer white_font("white_font.png");
    TextureBuffer black_font("black_font.png");
    TextureBuffer white("white.png");
    TextureBuffer black("black.png");
    TextureBuffer up("up.png");
    TextureBuffer down("down.png");


    Object basic(black, true, -2, nullptr);

    Object& menu_div = basic.utworz_obiekt(black);
        Object& sandbox_mode_button = menu_div.utworz_obiekt(white);
        Object& down_sign = menu_div.utworz_obiekt(down);
        Object& up_sign = menu_div.utworz_obiekt(up);
            Object& test_window = up_sign.utworz_okienko(white, &basic);
                Object& inside_window = test_window.utworz_obiekt(black);

    while(true)
    {

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        program.uzyj();

        Writing& welcome_sign = basic.utworz_tekst(wysokosc_bezwzgledna(50), szerokosc_bezwzgledna(30), (1 - wysokosc_bezwzgledna(300))/2.0 - wysokosc_bezwzgledna(25), white_font);
            welcome_sign.pisz("Welcome to");
            welcome_sign.kolejna_linia();
            welcome_sign.zmien_rozmiar(wysokosc_bezwzgledna(100), szerokosc_bezwzgledna(60));
            welcome_sign.pisz("EURO ELEVATOR Simulator!");
            welcome_sign.zmien_rozmiar(wysokosc_bezwzgledna(25), szerokosc_bezwzgledna(15));
            welcome_sign.kolejna_linia();
            welcome_sign.pisz("Release 2.0");


        menu_div.inicjalizuj(Object::CENTER, 0, 1 - wysokosc_bezwzgledna(50), 2, wysokosc_bezwzgledna(100));
            down_sign.inicjalizuj(Object::LEFT, 0, 0, szerokosc_bezwzgledna(100), wysokosc_bezwzgledna(100));
            up_sign.inicjalizuj(Object::RIGHT, 0, 0, szerokosc_bezwzgledna(100), wysokosc_bezwzgledna(100));
                test_window.inicjalizuj(Object::CENTER, 0, 0.5, 1, 1);
                    inside_window.inicjalizuj(Object::CENTER, 0, 0.25, 0.5, 0.5);
            sandbox_mode_button.inicjalizuj(Object::CENTER, 0, 0, szerokosc_bezwzgledna(700), wysokosc_bezwzgledna(100));
                Writing& sandbox_mode_button_text = sandbox_mode_button.utworz_tekst(wysokosc_bezwzgledna(50), szerokosc_bezwzgledna(30), wysokosc_bezwzgledna(25), black_font);
                    sandbox_mode_button_text.pisz("SANDBOX MODE");


        if(sandbox_mode_button.czy_wcisniety())
        {
            return 1;
        }

        if(up_sign.czy_wcisniety())
        {
            up_sign.aktywuj_okienko();
        }




        basic.rysuj();


        white_font.rysuj();
        black_font.rysuj();
        white.rysuj();
        black.rysuj();
        up.rysuj();
        down.rysuj();


        winxSwapBuffers();
		winxPollEvents();
//		czyszczenie();
//		cout<<cursor_x<<" "<<cursor_y<<endl;
    }

}

int wybor_ilosci_wind(ShaderProgram& program)
{

    int elevator_number=2;
    string text_input="";

    TextureBuffer white_font("white_font.png");
    TextureBuffer black_font("black_font.png");
    TextureBuffer white("white.png");
    TextureBuffer black("black.png");
    TextureBuffer down("down.png");

    Object basic(black, true, -2, nullptr);

    Object& text_box = basic.utworz_obiekt(white);
    Object& start_button = basic.utworz_obiekt(down);

    while(true)
    {

        program.uzyj();


        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        Writing& instruction = basic.utworz_tekst(wysokosc_bezwzgledna(50), szerokosc_bezwzgledna(30), (1 - wysokosc_bezwzgledna(300))/2.0 - wysokosc_bezwzgledna(25), white_font);
            instruction.pisz("SANDBOX MODE");
            instruction.kolejna_linia();
            instruction.zmien_margines(0.1);
            instruction.zmien_pozycjonowanie();
            instruction.zmien_rozmiar(wysokosc_bezwzgledna(30), szerokosc_bezwzgledna(18));
            instruction.pisz("To simulate calling an elevator from the hallway type: -1 <floor number> <direction>. Direction is either u - for going up or d - for going down.");
            instruction.pisz("This command will call the nearest elevator to the floor chosen.");
            instruction.kolejna_linia();
            instruction.pisz("To simulate sending a specific elevator somewhere using buttons in the elevator type: <elevator number> <floor number>.");
            instruction.kolejna_linia();
            instruction.kolejna_linia();
            instruction.pisz("Alternative way of controlling the elevators in the Sandbox Mode are Passengers.");
            instruction.kolejna_linia();
            instruction.pisz("Passenger is an entity simulating an actual person using the elevator. First it will summon one of the elevators to it's floor of origin.");
            instruction.pisz("As soon as the elevator arrives the passenger will automatically send it to the destination floor.");
            instruction.kolejna_linia();
            instruction.pisz("To create a new passenger type: -2 <floor of origin> <destination floor>");
            instruction.kolejna_linia();
            instruction.kolejna_linia();
            instruction.zmien_rozmiar(wysokosc_bezwzgledna(40), szerokosc_bezwzgledna(24));
            instruction.pisz("To start type the number of elevators you want to simulate and press Enter or click the white arrow below. Have fun!");
            instruction.zmien_rozmiar(wysokosc_bezwzgledna(25), szerokosc_bezwzgledna(15));
            instruction.pisz("Default elevator number is 2. If you type nothing and start, the simulation will launch with 2 elevators.");


        text_box.inicjalizuj(Object::CENTER, 0, 2 - wysokosc_bezwzgledna(600), 2, wysokosc_bezwzgledna(100));
            Writing& text_box_content = text_box.utworz_tekst(wysokosc_bezwzgledna(60), szerokosc_bezwzgledna(33), wysokosc_bezwzgledna(20), black_font);
                text_box_content.pisz(text_input);

        start_button.inicjalizuj(Object::CENTER, 0, 2 - wysokosc_bezwzgledna(300), szerokosc_bezwzgledna(150), wysokosc_bezwzgledna(150));


        if(start_button.czy_wcisniety() || enter_key_state)
        {
            stringstream ss;

            ss<<text_input;

            ss>>elevator_number;

            return elevator_number;
        }

        for(int g=0; g<10; g++)
        {
            if(number_keys_state[g])
            {
                text_input.push_back(cyfra_na_znak(g));
                spij(100);
            }
        }

        if(backspace_key_state)
        {
            if(text_input.size()>0)
            {
                text_input.pop_back();
            }
        }


        basic.rysuj();


        white_font.rysuj();
        black_font.rysuj();
        white.rysuj();
        black.rysuj();
        down.rysuj();


        winxSwapBuffers();
		winxPollEvents();
    }

}

void sterowanie()
{

    cout<<"Launching the Sandbox mode..."<<endl;
    for(int i=0;i<20;i++)
    {
        cout<<"/  ";
        spij(45);
    }

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

            char direction;

            if(elevator_number==-1)
            {
                cin>>direction;
            }

            wywolaj_winde(elevator_number, w, direction);

            wstrzymywanie=false;
        }
    }
}

