#include "Notepad.h"

Notepad::Notepad() {}

void Notepad::add_room()
{
    std::string name;
    std::cout << "\tEnter a location: ";

    bool doopy = true;
    while (doopy)     //till name is valid
    {
        getline(std::cin, name);
        if (name.length() != 0) {
            for (char n : name)
            {
                if (n != ' ' && n != '\t')
                {
                    doopy = false;
                    break;
                }
            }
        }
        if (doopy)std::cout << "\tLocation not entered, try again:\n";
    }

    while (name.at(0) == ' ' || name.at(0) == '\t')     //erasing empty spaces at the beginning of words
    {
        name.erase(0, 1);
    }

    for (int i{}; i < rooms.size(); i++)
    {
        if (rooms.at(i).get_name() == name)
        {
            std::cout << "\n\tSuch location already exists. [ " << i + 1 << ". ";
            rooms.at(i).show_overview();
            std::cout << " ]\n";
            return;
        }
    }

    rooms.push_back(Room(name));
    std::cout << "\n\tLocation added successfully!\n\n";

}

void Notepad::del_room()
{
    if (rooms.empty())
    {
        std::cout << "\n\tYou have no saved locations yet.\n\n";
        return;
    }
    int room_num;
    std::string msg{ "\n\tEnter location number you wish to delete: " };

    display_names();
    std::cout << "\t" << rooms.size() + 1 << ". Back\n";
    validate(room_num, msg);
    if (room_num == rooms.size()) return;

    rooms.erase(rooms.begin() + room_num);
    std::cout << "\n\tLocation deleted successfully!\n\n";
}

void Notepad::display() const
{
    if (rooms.empty())
    {
        std::cout << "\n\tYou have no locations yet!\n\n";
        return;
    }

    std::cout << "     -------------------------------------------------------------------\n";
    std::cout << "                                     Tasks\n";
    std::cout << "     -------------------------------------------------------------------\n\n";
    for (int i{}; i < rooms.size(); i++)
    {
        std::cout << "\t" << i + 1 << ". ";
        rooms.at(i).display();
    }
    std::cout << std::endl;
}

void Notepad::add_task_to_room()
{
    //if (rooms.empty())
    //{
    //    std::cout << "\n\tNo locations yet. In order to add tasks, save a location first.\n\n";
    //    return;
    //}
    //if (contractors.empty())
    //{
     //   std::cout << "\n\tNo contractors yet. In order to add tasks, save a contractor first.\n\n";
     //   return;
  //  }
    int room_num;
    std::string msg{ "\n\tEnter a location number to add a task to it: " };

    display_names();
    std::cout << "\t" << rooms.size()+1 << ". Add new\n";
    validate(room_num, msg);
    if (room_num == rooms.size()) add_room();

    std::string task = task_from_usr(room_num);

    while (task.at(0) == ' ' || task.at(0) == '\t')     //erasing empty spaces at the beginning of words
    {
        task.erase(0, 1);
    }

    const std::vector<Task>* tasks = rooms.at(room_num).get_tasks();    //get a pointer to a vector of tasks
    for (const Task& t : *tasks)
    {
        if (t.get_note() == task)      //if task already exists, don't save it again
        {
            std::cout << "\n\tSuch task already exists in this location.\n ";
            tasks = nullptr;
            return;
        }
    }

    
    display_contractors();
    std::cout << "\t\t" << contractors.size() + 1 << ". Add new\n";
    std::cout << "\n\tSelect contractor for the task: ";
    
    int cont_id;
    validate_cont(cont_id);
    if (cont_id == contractors.size()) add_contractor();

    rooms.at(room_num).add_task(task, contractors.at(cont_id));
    std::cout << "\n\tTask added successfully!\n";

}

std::string Notepad::task_from_usr(int num)
{
    std::string task;
    std::cout << "\n\tEnter a task you wish to add to the location [" << rooms.at(num).get_name() << "]:\n";
    while (true)     //otherwise user prompted till passes in a valid task
    {
        getline(std::cin, task);
        if (task.length() != 0) {
            for (char t : task)
            {
                if (t != ' ' && t != '\t') return task;
            }
        }
        std::cout << "\tNo task entered, try again:\n";
    }
}

void Notepad::del_from_room()
{
    if (rooms.empty())
    {
        std::cout << "\n\tNothing to delete - no locations yet.\n\n";
        return;
    }

    std::string num;
    int task_num;
    int room_num;

    std::string msg{ "\n\tEnter the location from which to delete a task: " };

    display_names();
    std::cout << "\t" << rooms.size() + 1 << ". Back\n";
    validate(room_num, msg);
    if (room_num == rooms.size()) return;

    if (rooms.at(room_num).get_num_tasks() == 0)
    {
        std::cout << "\n\tNo tasks in this location!\n";
        return;
    }

    std::cout << "\n\tTasks in this location: \n";
    rooms.at(room_num).display();

    std::cout << "\n\tEnter the task to delete: ";
    while (true) {
        getline(std::cin, num);
        std::istringstream ss{ num };
        if (ss >> task_num)
        {
            if (task_num >= 1 && task_num <= rooms.at(room_num).get_num_tasks())
            {
                break;
            }
        }
        std::cout << "\tNo task with such number, enter again: ";
    }

    task_num--;     //decrease so that the number corresponds to location in vector
    rooms.at(room_num).erase_task(task_num);
}

void Notepad::validate(int& room_num, std::string msg)      //makes sure the user enters valid input
{
    std::string str_num;
    std::cout << msg;
    while (true) {
        getline(std::cin, str_num);
        std::istringstream ss{ str_num };
        if (ss >> room_num)
        {
            if (room_num <= rooms.size() + 1 && room_num >= 1) break;
            

        }
        std::cout << "\tNo such location, try again: ";
    }
    room_num--;     //decreases the number by one in order to adjust it to vector indexes
}

void Notepad::display_names() const
{
    std::cout << "     -------------------------------------------------------------------\n";
    std::cout << "                                Locations \n";
    std::cout << "     -------------------------------------------------------------------\n\n";
    for (int i{}; i < rooms.size(); i++)
    {
        std::cout << "\t" << i + 1 << ". ";
        rooms.at(i).show_overview();
        std::cout << std::endl;
    }
    std::cout << "\n";
}

void Notepad::read_file()   
{
    std::ifstream ifile("Notepad.txt");
    if (!ifile)
    {
        std::cerr << "Couldn't find your notepad!";
        return;
    }

    int room_num{ 0 };
    std::string text;
    std::string cont;
    while (!ifile.eof())
    {
        getline(ifile, text);
        if (text != "")  rooms.push_back(Room(text));        //create a new room with a name from file
        while (text != "")      //once line is empty, it's a sign new room will start
        {
            getline(ifile, text);
            getline(ifile, cont);
            if (text != "")
            {
                rooms.at(room_num).add_task(text, cont);
                int cont_check{};
                for (std::string c : contractors)
                {
                    if (c == cont) cont_check++;
                }
                if (cont_check == 0)contractors.push_back(cont);
            }

        }
        room_num++;     //upon finding an empty line, we move over to the next room - room_num increases
    }
    ifile.close();
}

void Notepad::save_file() const
{
    std::ofstream ofile("Notepad.txt");
    if (!ofile)
    {
        std::cerr << "Couldn't find your notepad!";
        return;
    }

    for (const Room& r : rooms)
    {
        ofile << r.get_name() << std::endl;
        const std::vector<Task>* tasks = r.get_tasks();
        for (const Task& t : *tasks)
        {
            ofile << t.get_note() << std::endl;
            ofile << t.get_cont() << std::endl;
        }
        ofile << std::endl << std::endl;
    }
    ofile.close();
}


void Notepad::add_contractor()
{
    std::string name;
    std::cout << "\tEnter a contractor: ";

    bool doopy = true;
    while (doopy)     //till name is valid
    {
        getline(std::cin, name);
        if (name.length() != 0) {
            for (char n : name)
            {
                if (n != ' ' && n != '\t')
                {
                    doopy = false;
                    break;
                }
            }
        }
        if (doopy)std::cout << "\tContractor not entered, try again:\n";
    }

    while (name.at(0) == ' ' || name.at(0) == '\t')     //erasing empty spaces at the beginning of words
    {
        name.erase(0, 1);
    }
    
    for (int i{}; i < contractors.size(); i++)
    {
        if (contractors.at(i) == name)
        {
            std::cout << "\n\tSuch person already exists. [ " << i + 1 << ". " << contractors.at(i);
            std::cout << " ]\n";
            return;
        }
    }

    contractors.push_back(name);
    std::cout << "\n\tContractor added successfully!\n\n";

}

void Notepad::del_contractor()
{
    if (contractors.size() == 1 && !rooms.empty())
    {
        std::cout << "Cannot delete contractor - noone else to reassign tasks to. Delete a location first.\n";
        return;
    }
    else if (contractors.size() == 0 )
    {
        std::cout << "Noone to delte.\n";
        return;
    }

    display_contractors();
    std::cout << "\n\t\t" << contractors.size() + 1 << ". Back\n";
    std::cout << "Enter a contractor to delete: ";

    int cont_id;
    validate_cont(cont_id);
    if (cont_id == contractors.size()) return;

    std::string temp = contractors.at(cont_id);
    contractors.erase(contractors.begin() + cont_id);
    reassign_conts(temp);

}

void Notepad::validate_cont(int &cont_id)
{
    std::string cont;
    
    while (true) {
        getline(std::cin, cont);
        std::istringstream ss{ cont };
        if (ss >> cont_id)
        {
            if (cont_id <= contractors.size() +1 && cont_id >= 1) break;

        }
        std::cout << "\tNo such contractor, try again: ";
    }
    cont_id--;
}

void Notepad::display_contractors()
{
    std::cout<<"\tContractors:\n";
    for (int i{}; i < contractors.size(); i++)
    {
        std::cout << "\t\t" << i + 1 << ". " << contractors.at(i) << "\n";
    }
}

void Notepad::reassign_conts(std::string temp)
{
    std::vector<int> locs;
    for (auto& r : rooms)
    {
        locs = r.get_locations(temp);
        for (auto l : locs)
        {
            display_contractors();
            std::cout << "\tSelect contractor for the task: [ " << r.get_name() << ": "<< r.get_specific_task(l)<< " ]: ";

            int cont_id;
            validate_cont(cont_id);

            r.set_task_cont(l, contractors.at(cont_id));
        }


    }
}