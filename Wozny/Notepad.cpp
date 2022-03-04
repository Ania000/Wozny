#include "Notepad.h"

Notepad::Notepad() {}

// Displaying

void Notepad::display() const
{
    if (rooms.empty())
    {
        std::cout << "\n\tYou have no active tasks at this point!\n\n";
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

void Notepad::display_closed()const
{
    if (closed.empty())
    {
        std::cout << "\n\tYou have no closed tasks yet!\n\n";
        return;
    }

    std::cout << "     -------------------------------------------------------------------\n";
    std::cout << "                               Closed Contracts\n";
    std::cout << "     -------------------------------------------------------------------\n\n";
    for (int i{}; i < closed.size(); i++)
    {
        closed.at(i).display_task();
    }
    std::cout << std::endl;
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
}

void Notepad::display_contractors()const
{
    std::cout << "\n\tContractors:\n";
    for (int i{}; i < contractors.size(); i++)
    {
        std::cout << "\t\t" << i + 1 << ". " << contractors.at(i) << "\n";
    }
}

//Adding

void Notepad::add_task_to_room()
{

    int room_num;
    std::string msg{ "\n\tEnter a location number to add a task to it: " };

    display_names();
    std::cout << "\t" << rooms.size() + 1 << ". Add new\n";
    validate(room_num, msg);
    if (room_num == rooms.size()) add_room();

    std::string task = task_from_usr(room_num);

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
    std::cout << "\n\tTask added successfully!\n\n";

}

void Notepad::add_room()
{

    std::cout << "\tEnter a location: ";

    std::string name = get_text("Location");

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

void Notepad::add_contractor()
{

    std::cout << "\tEnter a contractor: ";

    std::string name = get_text("Contractor");

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

//Deleting

void Notepad::del_from_room()
{
    if (check_empty("\n\tYou have no active tasks at this moment. Nothing to close.\n\n")) return;

    std::string msg1{ "\n\tNothing to close - no locations yet.\n\n" };
    std::string msg2{ "\n\tEnter the location from which to close a task: " };
    std::string msg3{ "\n\tEnter the task to close: " };

    int task_num;
    int room_num;

    if (!select_task(msg1, msg2, msg3, task_num, room_num)) return;

    Task t = rooms.at(room_num).get_task_obj(task_num);

    t.set_room(rooms.at(room_num).get_name());

    t.task_overview();

    get_opinion(t);

    closed.push_back(t);

    rooms.at(room_num).erase_task(task_num);
}

void Notepad::del_room()
{
    if (check_empty("\n\tYou have nothing to delete - no locations yet.\n\n")) { return; }
    int room_num;
    std::string msg{ "\n\tEnter location number you wish to delete: " };

    display_names();
    std::cout << "\t" << rooms.size() + 1 << ". Back\n";
    validate(room_num, msg);
    if (room_num == rooms.size()) return;

    const std::vector<Task>* tasks_to_close = rooms.at(room_num).get_tasks();

    for (Task t : *tasks_to_close)
    {
        t.set_room(rooms.at(room_num).get_name());

        std::cout << std::endl;

        t.task_overview();

        get_opinion(t);
        
        closed.push_back(t);
    }
    

    rooms.erase(rooms.begin() + room_num);
    std::cout << "\n\tLocation deleted successfully!\n\n";
}

void Notepad::del_contractor()
{
    if (contractors.size() == 1 && !rooms.empty())
    {
        std::cout << "Cannot delete contractor - noone else to reassign tasks to. Delete a location first.\n";
        return;
    }
    else if (contractors.size() == 0)
    {
        std::cout << "\n\tNoone to delte.\n\n";
        return;
    }

    display_contractors();
    std::cout << "\n\t\t" << contractors.size() + 1 << ". Back\n\n";
    std::cout << "\tEnter a contractor to delete: ";

    int cont_id;
    validate_cont(cont_id);
    if (cont_id == contractors.size()) return;

    std::string temp = contractors.at(cont_id);
    contractors.erase(contractors.begin() + cont_id);
    reassign_conts(temp);

    std::cout << "\n\tContractor successfully deleted.\n";

}

void Notepad::clear_closed()
{
    if (closed.size() == 0)
    {
        std::cout << "\n\tYour archive is empty.\n\n";
        return;
    }

    std::cout << "\n\tAre you sure? by proceeding you will lose all your previous data.\n\tTo clear archive type YES, to go back enter pretty much anything else: ";
    std::string prompt;
    getline(std::cin, prompt);
    if (prompt != "YES")
    {
        std::cout << "\n\tSo... you chose to spare the archive... very well then.\n";
        return;
    }
    closed.clear();
    std::cout << "\n\tArchive cleared successfully.\n";
}

//Changing

void Notepad::reassign_conts(std::string temp)
{
    std::vector<int> locs;
    for (auto& r : rooms)
    {
        locs = r.get_locations(temp);
        for (auto l : locs)
        {
            display_contractors();
            std::cout << "\t\t" << contractors.size() + 1 << ". Add new\n";
            std::cout << "\tSelect contractor for the task: [ " << r.get_name() << ": " << r.get_specific_task(l) << " ]: ";

            int cont_id;
            validate_cont(cont_id);
            if (cont_id == contractors.size()) add_contractor();

            r.set_task_cont(l, contractors.at(cont_id));
        }


    }
}

void Notepad::change_cont()
{
    if (check_empty("\n\tYou have no active tasks at this moment. Nothing to reassign.\n\n")) return;
    std::string msg1{ "\n\tNothing to reassign - no locations yet.\n\n" };
    std::string msg2{ "\n\tEnter the location in which you have a task to reassign: " };
    std::string msg3{ "\n\tEnter the task to reassign to a different contractor: " };

    int task_num;
    int room_num;


    if (!select_task(msg1, msg2, msg3, task_num, room_num)) return;

    Room& r = rooms.at(room_num);

    display_contractors();
    std::cout << "\t\t" << contractors.size() + 1 << ". Add new\n";
    std::cout << "\tSelect contractor for the task: [ " << r.get_name() << ": " << r.get_specific_task(task_num) << " ]: ";

    int cont_id;
    validate_cont(cont_id);
    if (cont_id == contractors.size()) add_contractor();

    rooms.at(room_num).set_task_cont(task_num, contractors.at(cont_id));

    std::cout << "\n\tContractors reassigned successfully!\n";
}

//Files

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
            }

        }
        room_num++;     //upon finding an empty line, we move over to the next room - room_num increases
    }
    ifile.close();

    ifile.open("Contractors.txt");
    if (!ifile)
    {
        std::cerr << "Couldn't find your contractors!";
        return;
    }
    while (!ifile.eof())
    {
        getline(ifile, cont);
        if (cont != "") contractors.push_back(cont);
    }
    ifile.close();


    ifile.open("Closed.txt");
    if (!ifile)
    {
        std::cerr << "Couldn't find your archive!";
        return;
    }

    while (!ifile.eof())
    {

        std::string room, note, cont, review;
        float rating;

        getline(ifile, text);
        if (text == "") break;
        room = text;
        getline(ifile, text);
        note = text;
        getline(ifile, text);
        cont = text;
        getline(ifile, text);
        review = text;
        getline(ifile, text);
        std::stringstream ss{ text };
        ss >> rating;
        closed.push_back(Task(room, note, cont, review, rating));

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

    ofile.open("Contractors.txt");
    if (!ofile)
    {
        std::cerr << "Couldn't find your contractors!";
        return;
    }
    for (std::string cont : contractors)
    {
        ofile << cont << std::endl;
    }
    ofile.close();

    ofile.open("Closed.txt");
    if (!ofile)
    {
        std::cerr << "Couldn't find your archive!";
        return;
    }
    for (const Task& t : closed)
    {
        ofile << t.get_room() << std::endl;
        ofile << t.get_note() << std::endl;
        ofile << t.get_cont() << std::endl;
        ofile << t.get_review() << std::endl;
        ofile << t.get_rating() << std::endl;

    }
    ofile.close();
}

//Validation

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

bool Notepad::check_empty(std::string msg)
{
    if (rooms.size() == 0)
    {
        std::cout << msg;
        return true;
    }
    else return false;
}

//Getting input

std::string Notepad::task_from_usr(int num)
{

    std::cout << "\n\tEnter a task you wish to add to the location [" << rooms.at(num).get_name() << "]:\n";
    std::string task = get_text("Task");
    return task;

}

bool Notepad::select_task(std::string msg1, std::string msg2, std::string msg3, int &task_num, int &room_num)
{
    if (rooms.empty())
    {
        std::cout << msg1;
        return false;
    }

    std::string num;
    

    std::string msg{ msg2 };

    display_names();
    std::cout << "\t" << rooms.size() + 1 << ". Back\n";
    validate(room_num, msg);
    if (room_num == rooms.size()) return false;

    if (rooms.at(room_num).get_num_tasks() == 0)
    {
        std::cout << "\n\tNo tasks in this location!\n";
        return false;
    }

    std::cout << "\n\tTasks in this location: \n";
    rooms.at(room_num).display();

    std::cout << msg3;
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
    return true;
}

void Notepad::get_opinion(Task& t)
{
    std::cout << "\n\tEnter client's rating ( */10): ";
    float rating = get_rating();

    std::cout << "\tEnter client's reveiw:\n";
    std::string review = get_text("Review");

    t.set_review(review);
    t.set_rating(rating);
}

float Notepad::get_rating()
{
    float r;
    std::string rating;
    while (true) 
    {
        getline(std::cin, rating);
        std::stringstream ss{ rating };
        if (ss >> r)
        {
            if (r > 0 && r <= 10)
            {
                r =std::round(r);
                return r;
            }
        }
        std::cout<<"\tInvalid rating, enter again: ";
    }
}

std::string Notepad::get_text(std::string thing)
{
    std::string text;
    while (true)     
    {
        getline(std::cin, text);

        while (text.length() != 0 && (text.at(0) == ' ' || text.at(0) == '\t'))     //erasing empty spaces at the beginning of words
        {
            text.erase(0, 1);
        }

        if (text.length() != 0)  return text;

       std::cout << "\t"<<thing<<" not entered, try again:\n";
    }
}

