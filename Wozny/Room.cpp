#include "Room.h"

Room::Room() {}
Room::Room(std::string n) : name(n) {}


void Room::display()
{
	std::cout << name << ": \n";
	for (auto t : tasks)
	{
		std::cout << "\t> " << t << std::endl;
	}
}

void Room::add_task(std::string task)
{
	tasks.push_back(task);
}

void Room::erase_task()
{

}