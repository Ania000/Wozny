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
	std::vector<std::string> contractors;

	std::string task_from_usr(int num);
	void validate(int& room_num, std::string msg);
	void display_names() const;

	void display_contractors();
	void validate_cont(int& cont_id);
	void reassign_conts(std::string temp);
public:

	Notepad();

	void display() const;
	void add_task_to_room();
	void del_from_room();
	void add_room();
	void del_room();

	void add_contractor();
	void del_contractor();
	

	void read_file();
	void save_file() const;



};