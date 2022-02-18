#include "Room.h"

Room::Room() :num (0) {}
Room::Room(std::string s, int n) { name = s; num = n; }


void Room::display() const
{
	std::cout <<"\t"<<num<<". "<< name << ": \n";
	for (int i{0}; i < tasks.size(); i ++)
	{
		
		std::cout << "\t\t"<<i+1<<" > " << tasks.at(i) << std::endl;
	}
}

void Room::show_overview()
{
	//making sure that all number counts are lined up despite differing name lengths
	std::cout << "\t" << num<<". "<<name;
	if (num == 8 || num == 4 || num == 5)std::cout << "";     //rooms 4, 5 and 8 don't need an extra indent
	else std::cout << "\t";                                 //rest of the rooms just get a generic one
	std::cout << "\t\t[zadan:" << tasks.size() << "]" << "\n";
}

void Room::add_task(std::string task)
{
	tasks.emplace_back(task);
	std::cout << "\n\tPomyslnie dodano zadanie!\n";
}

void Room::erase_task(int num)
{
	tasks.erase(tasks.begin() + num);
	std::cout << "\n\tPomyslnie usunieto zadanie.\n";
}