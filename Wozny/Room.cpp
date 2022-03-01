#include "Room.h"

Room::Room() {}
Room::Room(std::string s) { name = s; }


void Room::display() const
{
	std::cout << name << ": \n";
	for (int i{ 0 }; i < tasks.size(); i++)
	{

		std::cout << "\t\t" << i + 1 << " > " << tasks.at(i).get_note()<<"\t"<< tasks.at(i).get_cont() << std::endl;
	}
}

void Room::show_overview() const
{
	std::cout << name;
	std::cout << "\t\t[no. tasks:" << tasks.size() << "]";
}

void Room::add_task(std::string task, std::string cont)
{
	tasks.emplace_back(task, cont);

}

void Room::erase_task(int num)
{
	tasks.erase(tasks.begin() + num);
	std::cout << "\n\tTask deleted successfully.\n";
}

std::vector<int> Room::get_locations(std::string temp)
{
	std::vector<int>loc;
	for (int i{}; i<tasks.size(); i++)
	{
		if (tasks.at(i).get_cont() == temp) loc.push_back(i);
	}
	return loc;		//returns locations in task vector of tasks to reassign
}