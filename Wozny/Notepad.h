#pragma once

//#include <iostream>
//#include <vector>
//#include <string>
#include <sstream>
#include <iomanip>
#include "Room.h"

class Notepad
{
private:

	std::vector<std::string> names;
	std::vector<Room> rooms;

	std::string get_task(int num);
	void validate(int& room_num, std::string msg);
	void display_names();
	

public:

	Notepad();
	Notepad(std::vector<std::string> &temp);

	void display();
	void add_task_to_room();
	void del_from_room();

	

};

