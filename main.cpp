#include <iostream>
#include <thread>
#include <windows.h>
#include <vector>
using namespace std;


vector <int> polecenia;


void setCursor(int x, int y)
{
     COORD c;
     c.X = x-1;
     c.Y = y-1;
     SetConsoleCursorPosition (GetStdHandle (STD_OUTPUT_HANDLE), c);
}

void sterowanie()
{
    while(true)
    {
    int w;
    cin>>w;
    setCursor(1,1);
    polecenia.push_back(w);
    }
}

int main()
{

thread t1(sterowanie);

 string status="full_stop";
 int last_floor_number=0;
 string door_status="open";
 int underway_Status=0;
 int last_targets_status=0;
 int pseudopointer=0;
 int current_destination=0;
 int cooldown=0;

    while(true)
    {
       system ("cls");
           //setCursor(0,0);
        cout<<status<<endl;
        cout<<door_status<<endl;
        cout<<last_floor_number<<endl;
//        cout<<current_destination<<endl;
//        for(int i=0;i<polecenia.size();i++)
//        {
//            cout<<polecenia[i]<<" ";
//        }
        Sleep(1000);
        if(cooldown==0)
        {

        if((last_targets_status!=polecenia.size()))
        {
          current_destination=polecenia[pseudopointer];
        }

        if(last_floor_number>current_destination)
        {
          status="underway, using gravity";
          door_status="closed";
        }

        if(last_floor_number<current_destination)
        {
            status="underway, using engine";
            door_status="closed";
        }

        if((status=="underway, using engine")||(status=="underway, using gravity"))
        {
            underway_Status++;
            for(int i=0;i<underway_Status;i++)
            {
            cout<<".";
            }
        }

        if(underway_Status==5)
        {
            if(status=="underway, using engine")
            {
                last_floor_number++;
            }

            if(status=="underway, using gravity")
            {
                last_floor_number=last_floor_number-1;
            }

            underway_Status=0;

            if(last_floor_number==current_destination)
            {
                cooldown=3;
                door_status="open";
                status="full_stop";
                pseudopointer++;
                last_targets_status++;
            }
        }
        }
        else{cooldown=cooldown-1;}

    }


}
