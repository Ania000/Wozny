

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <iomanip>
#include "Notepad.h"
#include "Room.h"
#include "Iohandler.h"


void save_n_prompt(Notepad &n)
{
    n.save_file();
    std::string ready;
    std::cout << "Press ENTER to return to MENU.";
    getline(std::cin, ready);
}


void main_loop(Notepad &notepad)
{
    Iohandler handler;
    while (true)
    {
        switch (handler.prompt())
        {
        case 1:
            handler.set_color('b');
            notepad.display();
            save_n_prompt(notepad);
            break;

        case 2:
            handler.set_color('g');
            notepad.add_task_to_room();
            save_n_prompt(notepad);
            break;

        case 3:
            handler.set_color('r');
            notepad.del_from_room();
            save_n_prompt(notepad);
            break;

        case 4:
            handler.set_color('g');
            notepad.add_room();
            save_n_prompt(notepad);
            break;

        case 5:
            handler.set_color('r');
            notepad.del_room();
            save_n_prompt(notepad);
            break;

        case 6:
            handler.set_color('g');
            notepad.add_contractor();
            save_n_prompt(notepad);
            break;

        case 7:
            handler.set_color('r');
            notepad.del_contractor();
            save_n_prompt(notepad);
            break;

        case 8:

        default:
            return;
        }
        
        system("cls");
    }
}


int main()
{   
    Notepad notepad;

    std::cout << std::endl << "                      HELLO THERE! (general Kenobi)\n\n";
    notepad.read_file();
    main_loop(notepad);
    std::cout << "\n                         SEE YA LATER!\n";
}



//Ps. this still looks like shit and is unbearably long but hopefully will work fine

//Pps. How the hell yall's code is so short, wtf, i really don't see how to make it more efficient and less complex???
// i mean i guess i could pack some stuff in notepad.cpp into functions, but then those functions would be pretty complex cuz they would need slightly different arguments every time
// so how... what am I doing wrong
//   `\_(*-*)_/`