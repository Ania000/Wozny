#include "Task.h"

Task::Task(std::string r, std::string n, std::string c, std::string re, float ra)
{
	room = r;
	note = n;
	contractor = c;
	review = re;
	rating = ra;
}

void Task::display_task() const
{
	std::cout << "\t > " << room << ": " << note <<"   ( "<<contractor<<" )\t\tRating: " << rating << "/10\tReview: " << review << "\n";
}

void Task::task_overview() const
{
	std::cout << "\tSummary of task [ " << room << ": " << note << " ]\t( " << contractor << " ):\n";
}