

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
    std::cout<<std::endl << std::setw(13) << " " << "DZIEN DOBRY PANIE WOZNY!\n";
    bool doopy{ true };
    do
    {
        switch (handler.prompt())
        {
        case 1:
            std::cout << 1 << std::endl;
            notepad.display();
            std::cout << "Kliknij enter aby wrocic do menu.";
            getline(std::cin, ready);
            break;

        case 2:
            std::cout << 2;
            notepad.add_task_to_room();
            std::cout << "Pomyslnie dodano zadanie!\n Kliknij enter aby wrocic do menu.";
            getline(std::cin, ready);

            break;

        case 3:
            std::cout << 3;
            notepad.del_from_room();
            std::cout << "Kliknij enter aby wrocic do menu.";
            getline(std::cin, ready);
            break;

        case 4:
            std::cout << 4;
            doopy = false;
            break;

        default:
            break;
        }
        
        system("cls");
    } while (doopy);
}


int main()
{
    std::vector<std::string> temp{ "1.Lobby", "2.Biuro_1", "3.Biuro_2", "4.Serwerownia_1", "5.Serwerownia_2", "6.Kuchnia", "7.Lazienka", "8.Sala Konferencyjna", "9.Magazyn",  "10.Kanciapa" };
    
    Notepad notepad{ temp };    //create a notepad with rooms listed in vector
    main_loop(notepad);

    std::cout << std::setw(15) << " " << "\nDO WIDZENIA PANIE WOZNY!\n";
}
