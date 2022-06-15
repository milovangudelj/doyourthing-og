#include <stdio.h>
#include <stdlib.h>

#include "Action.hh"
#include "Spinner.hh"

using namespace std;
using namespace dyt;

Action::Action(std::string &name, std::vector<std::string> &commands) : _name{name}, _commands{commands}
{
}

Action::Action(const char *name, std::vector<std::string> &commands) : _name{std::string(name)}, _commands{commands}
{
}

Action::~Action()
{
}

/**
 * @brief Run the list of commands that make up the action.
 *
 * @return int Overall result of the action. 0 if successful, greater than 0 otherwise.
 */
int Action::run()
{
	int result = 0;

	Spinner spinner(_name);
	spinner.start();

	for (auto command : _commands)
	{
		result += system(command.c_str());
	}

	spinner.stop(result == 0);

	return result;
}

std::string Action::name() const
{
	return _name;
}