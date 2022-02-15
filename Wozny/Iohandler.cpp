#include "Iohandler.h"

int Iohandler::prompt()
{
    std::string choice;
    int c;

    menu();

    do
    {
        getline(std::cin, choice);     // we read into a char

    } while (!check(choice, c));     //break out of the loop once choice is valid

    system("cls");
    return c;      //return int
}

void Iohandler::menu()
{
    std::cout <<std::setw(5)<<" " << std::setw(40) << std::setfill('-') << " "<<std::setfill(' ')<<"\n";
    std::cout << "     " <<std::setw(21)<< " MENU " << "\n";
    std::cout << std::setfill('-') << "     " << std::setw(40) << " " << std::setfill(' ') << "\n\n";
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

    std::cout << "Taki wybor nie istnieje!\nSproboj jeszcze raz: ";
    return false;

}