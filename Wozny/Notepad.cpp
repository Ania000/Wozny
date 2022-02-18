#include "Notepad.h"

Notepad::Notepad() {}
void Notepad::add_rooms(std::vector<std::string> &temp) 
{
    int n = 1;
    for (std::string t : temp)
    {
        rooms.emplace_back(t, n);      //adding a new Room to vector and thus calling Room() with string and int
        n++;
    }
}

void Notepad::display()
{
    std::cout << "     -------------------------------------------------------------------\n";
    std::cout << "                                  Spis Zadan " << "\n";
    std::cout << "     -------------------------------------------------------------------\n\n";
    for (const Room &r : rooms)
    {
        r.display();
    }
    std::cout << std::endl;
}

void Notepad::add_task_to_room()
{
    int room_num;
    std::string msg{ "\n\tPodaj numer pomieszczenia, do ktorego chcesz dodac zadanie: " };
    
    display_names();
    validate(room_num, msg);

    std::string task = task_from_usr(room_num);
    rooms.at(room_num).add_task(task);
}

std::string Notepad::task_from_usr(int num)
{
    std::string task;
    std::cout << "\n\tPodaj zadanie, ktore chcesz dodac do pokoju [" << rooms.at(num).get_name() << "]:\n";
    while (true)     //otherwise user prompted till passes in a valid task
    {
        getline(std::cin, task);
        if (task.length() != 0) {
            for (char t : task)
            {
                if (t != ' ') return task;
            }
        }

        std::cout << "\tNie wpisano zadania, podaj jeszcze raz:\n";
    } 
}

void Notepad:: del_from_room()
{
    std::string num;
    int task_num;
    int room_num;
    bool doopy = true;

    std::string msg{ "\n\tPodaj numer pomieszczenia, z ktorego chcesz usunac zadanie: " };

    display_names();
    validate(room_num, msg);

    if (rooms.at(room_num).get_num_tasks() == 0)
    {
        std::cout << "\n\tNie ma zadan w tym pomieszczeniu!\n";
        return;
    }

    std::cout << "\n\tZadania w tym pomieszczeniu: \n";
    rooms.at(room_num).display();

    std::cout << "\n\tPodaj, ktore zadanie chcesz usunac: ";

    while (doopy) {
        getline(std::cin, num);
        std::istringstream ss{ num };
        if (ss >> task_num)
        {
            if (task_num >= 1 && task_num <= rooms.at(room_num).get_num_tasks())
            {
                doopy = false;
                break;
            }

        }
        std::cout << "\tNie istnieje zadanie o takim numerze, podaj ponownie: ";
    }

    task_num--;     //decrease so that the number corresponds to location in vector
    rooms.at(room_num).erase_task(task_num); 
}

void Notepad::validate(int &room_num, std::string msg)      //makes sure the user enters valid input
{
    std::string str_num;
    bool doopy = true;

    std::cout << msg;
    while (doopy) {
        getline(std::cin, str_num);
        std::istringstream ss{ str_num };
        if (ss >> room_num)
        {
            if (room_num <= rooms.size() && room_num >= 1)
            {
                doopy = false;
                break;
            }

        }
        std::cout << "\tTakie pomieszczenie nie istnieje, sporobuj jeszcze raz: ";
    }
    room_num--;
}

void Notepad::display_names()
{
    std::cout << "     -------------------------------------------------------------------\n";
    std::cout << "                                Pomieszczenia " << "\n";
    std::cout << "     -------------------------------------------------------------------\n\n";
    for (auto r : rooms)
    {
        r.show_overview();
    }
    std::cout << "\n";
}