#include "Iohandler.h"

int Iohandler::prompt()
{
    std::string choice;
    int c;

    menu();

    //here, I actually need do while(), so that first, the input is taken from the user, and then check() is called on that input
    //while loop causes validation to happen before taking the value
    do
    {
        getline(std::cin, choice);     // we read into a char

    } while (!check(choice, c));     //break out of the loop once choice is valid   

    system("cls");
    return c;      //return int
}

void Iohandler::menu()
{
    set_color('w');
    std::cout << "     -------------------------------------------------------------------\n";
    std::cout <<"                                    MENU\n";
    std::cout << "     -------------------------------------------------------------------\n\n";
    std::cout << "     1. Display active tasks\n"
        << "     2. Display closed tasks\n"
        << "     3. Add a new task\n"
        << "     4. Close a task\n"
        << "     5. Add a location\n"
        << "     6. Delete a location\n"
        << "     7. Add a contractor\n"
        << "     8. Delete a contractor\n"
        << "     9. Change contractor for a task\n"
        << "     10. Clear archive\n"
        << "     0. Quit(t)\n\n"
        << "\tChoice: ";
}

bool Iohandler::check(std::string choice, int& c)
{
    std::istringstream ss{ choice };
    ss >> c;
    if (c || c==0) //if failed, skip            number 0 is treated as false
    {
        if (c >= 0 && c <= 10) return true;
    }

    std::cout << "\tNo such option!\n\tEnter again: ";
    return false;

}

void Iohandler::set_color(char c)
{

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    switch (c)
    {
    case 'g':
        SetConsoleTextAttribute(handle, 2);
        break;
    case 'b':
        SetConsoleTextAttribute(handle, 3);
        break;
    case 'r':
        SetConsoleTextAttribute(handle, 4);
        break;
    case 'w':
    default:
        SetConsoleTextAttribute(handle, 7);
    }
    
}