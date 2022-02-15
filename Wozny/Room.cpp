#include "Room.h"

Room::Room() {}
Room::Room(std::string n) : name(n) {}


void Room::display() const
{
	std::cout <<"\t"<< name << ": \n";
	for (int i{0}; i < tasks.size(); i ++)
	{
		
		std::cout << "\t\t"<<i+1<<" > " << tasks.at(i) << std::endl;
	}
}

void Room::add_task(std::string task)
{
	tasks.emplace_back(task);
}

void Room::erase_task(int num)
{
	tasks.erase(tasks.begin() + num);
	std::cout << "Pomyslnie usunieto zadanie.\n";
}