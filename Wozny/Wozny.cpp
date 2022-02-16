

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <iomanip>
#include "Notepad.h"
#include "Room.h"
#include "Iohandler.h"

void main_loop(Notepad &notepad)
{
    Iohandler handler;
    std::string ready;
    std::cout<<std::endl << "                         DZIEN DOBRY PANIE WOZNY!\n\n";
    bool doopy{ true };
    while (doopy)
    {
        switch (handler.prompt())
        {
        case 1:
            handler.set_color('b');
            notepad.display();
            std::cout << "Kliknij enter aby wrocic do menu.";
            getline(std::cin, ready);
            break;

        case 2:
            handler.set_color('g');
            notepad.add_task_to_room();
            std::cout << "Kliknij enter aby wrocic do menu.";
            getline(std::cin, ready);

            break;

        case 3:
            handler.set_color('r');
            notepad.del_from_room();
            std::cout << "Kliknij enter aby wrocic do menu.";
            getline(std::cin, ready);
            break;

        case 4:
            doopy = false;
            break;

        default:
            break;
        }
        
        system("cls");
    }
}


int main()
{
    std::vector<std::string> temp{ "1.Lobby", "2.Biuro_1", "3.Biuro_2", "4.Serwerownia_1", "5.Serwerownia_2", "6.Kuchnia", "7.Lazienka", "8.Sala Konferencyjna", "9.Magazyn",  "10.Kanciapa" };
    
    Notepad notepad;    //create a notepad with rooms listed in vector
    notepad.add_rooms(temp);
    main_loop(notepad);

    std::cout << "\n                       DO WIDZENIA PANIE WOZNY!\n";
}


//That's just a check to see if commits work properly
//Ignore my dumb ass

//Ps. this still looks like shit and is unbearably long but hopefully wil work fine