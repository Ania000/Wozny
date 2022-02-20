

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <iomanip>
#include "Notepad.h"
#include "Room.h"
#include "Iohandler.h"

void prompt()
{
    std::string ready;
    std::cout << "Press ENTER to return to MENU.";
    getline(std::cin, ready);
}

void main_loop(Notepad &notepad)
{
    Iohandler handler;
    std::cout<<std::endl << "                               HELLO THERE!\n\n";
    while (true)
    {
        switch (handler.prompt())
        {
        case 1:
            handler.set_color('b');
            notepad.display();
            prompt();
            break;

        case 2:
            handler.set_color('g');
            notepad.add_task_to_room();
            prompt();
            break;

        case 3:
            handler.set_color('r');
            notepad.del_from_room();
            prompt();
            break;

        case 4:
            handler.set_color('g');
            notepad.add_room();
            prompt();
            break;

        case 5:
            handler.set_color('r');
            notepad.del_room();
            prompt();
            break;

        case 6:

        default:
            return;
        }
        
        system("cls");
    }
}


int main()
{   
    Notepad notepad;   

    notepad.read_file();
    main_loop(notepad);
    notepad.save_file();
    std::cout << "\n                       SEE YA LATER!\n";
}


//That's just a check to see if commits work properly
//Ignore my dumb ass

//Ps. this still looks like shit and is unbearably long but hopefully wil work fine