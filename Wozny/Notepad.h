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
	std::vector<Task> closed;

	//Displaying
	void display_names() const;
	void display_contractors() const;

	//Interaction with user
	void get_opinion(Task& t);
	std::string get_text(std::string thing);
	float get_rating();
	std::string task_from_usr(int num);
	void select_task(std::string msg1, std::string msg2, std::string msg3, int& task_num, int& room_num);

	//Validation
	void validate(int& room_num, std::string msg);
	void validate_cont(int& cont_id);
	bool check_empty(std::string msg);


	void reassign_conts(std::string temp);

	
	

public:

	Notepad();

	//Display
	void display_closed() const;
	void display() const;

	//Tasks
	void add_task_to_room();
	void del_from_room();

	//Locations
	void add_room();
	void del_room();

	//Contractors
	void add_contractor();
	void del_contractor();
	void change_cont();
	
	//Files
	void read_file();
	void save_file() const;

	void clear_closed();

};