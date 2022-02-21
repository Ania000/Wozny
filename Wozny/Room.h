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

	inline int get_num_tasks() const { return static_cast<int>(tasks.size()); }
	inline std::string get_name() const { return name; }
	inline const std::vector<std::string>* get_tasks() const { return &tasks; }		//returns pointer to the vector, no need to copy the whole vector

	void display() const;
	void show_overview() const;

	void add_task(std::string task);
	void erase_task(int num);
	

};

#endif //ROOM_H