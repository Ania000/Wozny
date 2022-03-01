#pragma once

#include <iostream>
#include <string>

class Task
{
private:
	std::string contractor;
	std::string note;
	float rating;
	std::string review;

public:
	Task(std::string n, std::string c) { note = n; contractor = c; rating = 0; }
	Task() { rating = 0; }

	inline std::string get_note() const { return note; }
	inline std::string get_cont() const { return contractor; }

	inline void set_cont(std::string cont) { contractor = cont; }
};

