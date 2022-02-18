#pragma once

#include <sstream>
#include <iomanip>
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
	void add_rooms(std::vector<std::string>& temp);


	

};

