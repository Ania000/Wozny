#ifndef	ROOM_H
#define ROOM_H

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "Task.h"

class Room
{
private:
	std::string name;
	std::vector<Task> tasks;

public:
	Room();
	Room(std::string s);

	inline int get_num_tasks() const { return static_cast<int>(tasks.size()); }
	inline std::string get_name() const { return name; }
	inline const std::vector<Task>* get_tasks() const { return &tasks; }		//returns pointer to the vector, no need to copy the whole vector

	void display() const;
	void show_overview() const;

	void add_task(std::string task, std::string cont);
	void erase_task(int num);

	inline std::string get_specific_task(int i) { return tasks.at(i).get_note(); }

	inline void set_task_cont(int i, std::string cont) { tasks.at(i).set_cont(cont); }

	std::vector<int> get_locations(std::string temp);


};

#endif //ROOM_H