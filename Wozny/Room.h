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
	Room(std::string s);

	inline std::string get_name() const { return name; }

	void display() const;
	void show_overview();

	void add_task(std::string task);
	void erase_task(int num);
	inline int get_num_tasks() { return tasks.size(); }

	std::vector<std::string> get_tasks() const;


};

#endif //ROOM_H