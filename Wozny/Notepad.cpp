#include "Notepad.h"

Notepad::Notepad() {}
Notepad::Notepad(std::vector<std::string>& temp) 
{
    for (std::string t : temp)
    {
        rooms.emplace_back(t);
    }
    names = temp;

    temp.~vector();
}

void Notepad::display()
{
    std::cout << std::setw(5) << " " << std::setw(40) << std::setfill('-') << " " << std::setfill(' ') << "\n";
    std::cout << "     " << std::setw(13)<<" " << " Spis Zadan " << "\n";
    std::cout << std::setfill('-') << "     " << std::setw(40) << " " << std::setfill(' ') << "\n\n";
    for (const Room &r : rooms)
    {
        r.display();
    }
    std::cout << std::endl;
}

void Notepad::add_task_to_room()
{
    int room_num;
    std::string msg{ "Podaj numer pomieszczenia, do ktorego chcesz dodac zadanie: " };
    
    display_names();
    validate(room_num, msg);

    std::string task = get_task(room_num);
    rooms.at(room_num).add_task(task);
}

std::string Notepad::get_task(int num)
{
    std::string task;
    std::cout << "Podaj zadanie, ktore chcesz dodac do pokoju [" << rooms.at(num).get_name() << "]:\n";
    do
    {
        getline(std::cin, task);
        if (task.length() != 0) return task;        //if string not empty, it's returned as task
        std::cout << "Nie wpisano zadania, podaj jeszcze raz:\n";
    } while (true);     //otherwise user prompted till passes in a valid task
}

void Notepad:: del_from_room()
{
    std::string num;
    int task_num;
    int room_num;
    bool doopy = true;

    std::string msg{ "Podaj numer pomieszczenia, z ktorego chcesz usunac zadanie: " };

    display_names();
    validate(room_num, msg);

    if (rooms.at(room_num).get_num_tasks() == 0)
    {
        std::cout << "Nie ma zadan w tym pomieszczeniu!\n";
        return;
    }

    std::cout << "Zadania w tym pomieszczeniu: \n";
    rooms.at(room_num).display();

    std::cout << "Podaj, ktore zadanie chcesz usunac: ";

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
        std::cout << "Nie istnieje zadanie o takim numerze, podaj ponownie: ";
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
        std::cout << "Takie pomieszczenie nie istnieje, sporobuj jeszcze raz: ";
    }
    room_num--;
}

void Notepad::display_names()
{
    std::cout << "[ ";
    for (auto n : names) std::cout << n<<" ";
    std::cout << "]\n";
}