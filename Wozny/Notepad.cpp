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
                if (n != ' ' && n!= '\t')
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
            std::cout<< " ]\n";
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
    validate(room_num, msg);

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
    for (int i{}; i<rooms.size(); i++)
    {
        std::cout <<"\t"<< i + 1 << ". ";
        rooms.at(i).display();
    }
    std::cout << std::endl;
}

void Notepad::add_task_to_room()
{
    if (rooms.empty())
    {
        std::cout << "\n\tNo locations yet. In order to add tasks, save a location first.\n\n";
        return;
    }
    int room_num;
    std::string msg{ "\n\tEnter a location number to add a task to it: " };
    
    display_names();
    validate(room_num, msg);

    std::string task = task_from_usr(room_num);

    while (task.at(0) == ' ' || task.at(0) == '\t')     //erasing empty spaces at the beginning of words
    {
        task.erase(0, 1);
    }

    const std::vector<std::string> *tasks = rooms.at(room_num).get_tasks();    //get a pointer to a vector of tasks
    for (const std::string &t : *tasks)
    {
        if (t == task)      //if task already exists, don't save it again
        {
            std::cout << "\n\tSuch task already exists in this location.\n ";
            tasks = nullptr;
            return;
        }
    }

    rooms.at(room_num).add_task(task);
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

void Notepad:: del_from_room()
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
    validate(room_num, msg);

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
        std::cout << "\tNo such location, try again: ";
    }
    room_num--;     //decreases the number by one in order to adjust it to vector indexes
}

void Notepad::display_names() const
{
    std::cout << "     -------------------------------------------------------------------\n";
    std::cout << "                                Locations \n";
    std::cout << "     -------------------------------------------------------------------\n\n";
    for (int i{}; i<rooms.size(); i++)
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
    while (!ifile.eof())
    {
        getline(ifile, text);
        if(text != "")  rooms.push_back(Room(text));        //create a new room with a name from file
        while (text != "")      //once line is empty, it's a sign new room will start
        {
            getline(ifile, text);
            if (text != "") rooms.at(room_num).add_task(text);
            
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

    for (const Room &r : rooms)
    {
        ofile << r.get_name() << std::endl;
        const std::vector<std::string> *tasks = r.get_tasks();
        for (const std::string &t : *tasks)
        {
            ofile << t << std::endl;
        }
        ofile<<std::endl;
    }
    ofile.close();
}