

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <iomanip>
#include "Room.h"

bool check(char choice, int& c)
{
    c = static_cast<int>(choice);       //try to convert a char into int
    c -= 48;            //get the right int value accoring to ASCII
    if (c) //if failed, skip
    {
        if (c >= 1 && c <= 4) return true;
    }

    std::cout << "Taki wybor nie istnieje!\nSproboj jeszcze raz: ";
    return false;

}

int prompt()
{
    char choice;
    int c;
    std::cout << "\nCo chcesz dzis zrobic?:\n"
        << "1. Wyswietl zadania\n"
        << "2. Dodaj nowe zadanie\n"
        << "3. Usun wykonane zadanie\n"
        << "4. Zakoncz\n"
        << "Twoj wybor: ";
    do
    {
        std::cin >> choice;     // we read into a char

    } while (!check(choice, c));     //break out of the loop once choice is valid

    return c;      //return int
}

void setup_rooms(std::vector<Room>* rooms, std::vector<std::string>* temp)
{
    for (std::string t : *temp)
    {
        rooms->push_back(t);
    }
    temp->~vector();

}

std::string get_task(std::string name)
{
    std::string task;
    std::cin.ignore();      //clear input from before
    std::cout << "Podaj zadanie, ktore chcesz dodac do pokoju [" << name << "]:\n";
    do
    {
        getline(std::cin, task);
        if (task.length() != 0) return task;        //if string not empty, it's returned as task
        std::cout << "Nie wpisano zadania, podaj jeszcze raz:\n";
    } while (true);     //otherwise user prompted till passes in a valid task
}

void add_task_to_room(std::vector<Room>* rooms)
{
    int room_num;
    Room* room{};

    std::cout << "Podaj numer pomieszczenia, do ktorego chcesz dodac zadanie: ";
    std::cin >> room_num;

    room = &rooms->at(room_num - 1);        //create a pointer to the disireable room
    room->add_task(get_task(room->get_name()));

}

void main_loop(std::vector<Room>* rooms)
{
    std::cout << std::setw(15) << " " << "DZIEN DOBRY PANIE WOZNY!\n";
    bool doopy{ true };
    do
    {
        switch (prompt())
        {
        case 1:
            std::cout << 1 << std::endl;
            for (auto r : *rooms)
            {
                r.display();
            }
            std::cout << "Pomyslnie dodano zadanie!\n Kliknij enter aby wrocic do menu.";
            std::cin.ignore();
            break;

        case 2:
            std::cout << 2;
            add_task_to_room(rooms);
            std::cout << "Pomyslnie dodano zadanie!\n Kliknij enter aby wrocic do menu.";

            break;

        case 3:
            std::cout << 3;
            break;

        case 4:
            std::cout << 4;
            doopy = false;
            break;

        default:
            break;
        }
        std::string ready;
        getline(std::cin, ready);
        system("cls");
    } while (doopy);
}

int main()
{
    std::vector<std::string> temp{ "1. Lobby", "2. Biuro 1", "3. Biuro 2", "4. Serwerownia 1", "5. Serwerownia 2", "6. Kuchnia", "7. Lazienka", "8. Sala Konferencyjna", "9. Magazyn",  "10. Kanciapa" };
    std::vector<Room> rooms;
    setup_rooms(&rooms, &temp);

    main_loop(&rooms);
    std::cout << std::setw(15) << " " << "\nDO WIDZENIA PANIE WOZNY!\n";
}
