#pragma once

//rooms to be interpreted as locations
//Room: Location

#include <sstream>
#include <iomanip>
#include <fstream>
#include "Room.h"

class Notepad
{
private:

	std::vector<Room> rooms;

	std::string task_from_usr(int num);
	void validate(int& room_num, std::string msg);
	void display_names();
	

public:

	Notepad();

	void display();
	void add_task_to_room();
	void del_from_room();
	void add_room();
	void del_room();

	void read_file();
	void save_file() const;

	

};

