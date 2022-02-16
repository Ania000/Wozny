#include "Notepad.h"

Notepad::Notepad() {}
void Notepad::add_rooms(std::vector<std::string> &temp) 
{
    for (std::string t : temp)
    {
        rooms.emplace_back(t);
    }

    temp.clear();
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

    std::string task = get_task(room_num);
    rooms.at(room_num).add_task(task);
}

std::string Notepad::get_task(int num)
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
        //making sure that all number counts are lined up despite differing name lengths
        std::cout << "\t" << r.get_name();
        if (r.get_name().at(0) == '1' && r.get_name().at(1) != '0')std::cout << "\t\t";     //first room needs one more indentation then the rest
        else if (r.get_name().at(0) == '8')std::cout << "";     //eight needs one less
        else std::cout << "\t";                                 //rest of the rooms just get a generic one
        std::cout<<"\t\t[zadan:" << r.get_num_tasks() << "]" << "\n";
    }
    std::cout << "\n";
}