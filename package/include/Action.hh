#ifndef ACTION_H
#define ACTION_H

#include <vector>
#include <string>

namespace dyt
{

	/**
	 * @brief Class representing a single action to be performed by the program.
	 *
	 */
	class Action
	{
	private:
		/// The name of the action
		std::string _name;

		/// The list of commands to be executed as part of the action
		std::vector<std::string> _commands;

	public:
		Action(std::string &name, std::vector<std::string> &commands);
		Action(const char *name, std::vector<std::string> &commands);
		~Action();

		int run();

		std::string name() const;
	};

} // namespace dyt

#endif // ACTION_H