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
    std::cout<< "     1. Wyswietl zadania\n"
        << "     2. Dodaj nowe zadanie\n"
        << "     3. Usun wykonane zadanie\n"
        << "     4. Zakoncz\n\n"
        << "\tTwoj wybor: ";
}

bool Iohandler::check(std::string choice, int& c)
{
    std::istringstream ss{ choice };
    ss >> c;
    //c -= 48;            //get the right int value accoring to ASCII
    if (c) //if failed, skip
    {
        if (c >= 1 && c <= 4) return true;
    }

    std::cout << "\tTaki wybor nie istnieje!\nSproboj jeszcze raz: ";
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