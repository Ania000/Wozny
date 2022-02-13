#ifndef	ROOM_H
#define ROOM_H

#include <iostream>
#include <string>
#include <list>
#include <vector>

class Room
{
private:
	std::string name;
	std::vector<std::string> tasks;

public:
	Room();
	Room(std::string n);

	inline std::string get_name() { return name; }

	void display();

	void add_task(std::string task);
	void erase_task();


};

#endif //ROOM_H