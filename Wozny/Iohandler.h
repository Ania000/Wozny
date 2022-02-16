#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <Windows.h>

class Iohandler
{
public:
	Iohandler() { }

	int prompt();
	void set_color(char c);

private:
	void menu();
	bool check(std::string choice, int& c);

};

