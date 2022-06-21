#include <stdlib.h>

#include "Action.hh"
#include "Section.hh"

using namespace std;
using namespace dyt;

Section::Section(const std::string &name, const std::vector<Action> &actions) : _name{name}, _actions{actions}, _successful{0}, _failed{0}
{
}

Section::~Section()
{
}

std::string Section::name() const
{
	return _name;
}

int Section::successful() const
{
	return _successful;
}

int Section::failed() const
{
	return _failed;
}

/**
 * @brief Run the list of actions that make up the Section.
 *
 *
 */
void Section::run_actions()
{
	for (auto action : _actions)
	{
		if (action.run() == 0)
		{
			_successful++;
		}
		else
		{
			_failed++;
		}
	}
}