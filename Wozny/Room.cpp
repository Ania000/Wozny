#include "Room.h"

Room::Room() {}
Room::Room(std::string s) { name = s; }


void Room::display() const
{
	std::cout << name << ": \n";
	for (int i{0}; i < tasks.size(); i ++)
	{
		
		std::cout << "\t\t"<<i+1<<" > " << tasks.at(i) << std::endl;
	}
}

void Room::show_overview()
{
	std::cout <<name;
	std::cout << "\t\t[no. tasks:" << tasks.size() << "]" << "\n";
}

void Room::add_task(std::string task)
{
	tasks.emplace_back(task);
	
}

void Room::erase_task(int num)
{
	tasks.erase(tasks.begin() + num);
	std::cout << "\n\tTask deleted successfully.\n";
}

std::vector<std::string> Room::get_tasks() const
{
	return tasks;
}