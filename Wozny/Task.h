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
	std::string room;		//for data on closed notes

public:
	Task(std::string r, std::string n, std::string c, std::string re, float ra);
	Task(std::string n, std::string c) { note = n; contractor = c; rating = 0; }
	Task() { rating = 0; }

	inline std::string get_note() const { return note; }
	inline std::string get_cont() const { return contractor; }
	inline std::string get_room() const { return room; }
	inline std::string get_review() const { return review; }
	inline float get_rating() const { return rating; }

	inline void set_cont(std::string cont) { contractor = cont; }
	inline void set_rating(float r) { rating = r; }
	inline void set_review(std::string r) { review = r; }
	inline void set_room(std::string r) { room = r; }

	void display_task() const;
	void task_overview() const;
};

