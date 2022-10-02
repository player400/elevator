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

void sterowanie();

int main()
{

//    cout<<"Welcome to EURO ELEVATOR Simulator 2.0 - PASSENGER UPDATE!"<<endl;
//    cout<<"Press 1 to launch the Sandbox Mode"<<endl;
//    int modenumber=0;
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

    ile_wind=2;

    for(int i=0;i<ile_wind;i++)
    {
        ElevatorData pustawinda(i);
        windy.push_back(pustawinda);
    }

    czyszczenie();

    thread t1(sterowanie);

    wstrzymywanie=false;

    winxHint(WINX_HINT_OPENGL_MAJOR, 3);
    winxHint(WINX_HINT_OPENGL_MINOR, 3);
    winxHint(WINX_HINT_OPENGL_CORE, true);
    winxHint(WINX_HINT_VSYNC, WINX_VSYNC_ENABLED);

    window_width=1000;
    window_height=600;

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


    //stbi_set_flip_vertically_on_load(true);


    Object basic("test.png", true, -2, nullptr);

    Object& test_rectangle = basic.utworz_obiekt("font.png");
    Object& inside_rectangle = test_rectangle.utworz_obiekt("test.png");



    while(true)
    {

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        test_rectangle.inicjalizuj(Object::CENTER, 0, wysokosc_bezwzgledna(400), szerokosc_bezwzgledna(700), wysokosc_bezwzgledna(400));
        inside_rectangle.inicjalizuj(Object::LEFT, 0, wysokosc_bezwzgledna(100), szerokosc_bezwzgledna(350), wysokosc_bezwzgledna(200));

        Writing& writing=basic.utworz_tekst(wysokosc_bezwzgledna(60), szerokosc_bezwzgledna(50), 0, "font.png");

        writing.pisz("Hello world!");
        writing.pisz("I'm a nice little window");
        writing.kolejna_linia();
        writing.zmien_pozycjonowanie();
        writing.pisz("winx is my god");
        writing.zmien_margines(0.3);
        writing.pisz("Bill Gates has brought me to life");
        writing.zmien_pozycjonowanie();
        writing.zmien_rozmiar(wysokosc_bezwzgledna(90), szerokosc_bezwzgledna(75));
        writing.pisz("winx - Powered by WinAPI");

//        czyszczenie();
//        cout<<"LINIA"<<endl;
//        exit(1);


        program.uzyj();

        basic.rysuj();


        winxSwapBuffers();
		winxPollEvents();
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
//        texture.bind();
       // buffer.rysuj();
//        writing.rysuj();

        winxSwapBuffers();
		winxPollEvents();
    }
    return 0;
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

