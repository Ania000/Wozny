#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

class Iohandler
{
public:
	Iohandler() { }

	int prompt();

private:
	void menu();
	bool check(std::string choice, int& c);

};

