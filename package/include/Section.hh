#ifndef SECTION_H
#define SECTION_H

#include <vector>
#include <string>

#include "Action.hh"

namespace dyt
{

	/**
	 * @brief Class representing a section containing one or more actions.
	 *
	 */
	class Section
	{
	private:
		/// The name of the section
		std::string _name;

		/// The list of actions composing the Section
		std::vector<Action> _actions;

		/// Number of successful actions
		int _successful;
		/// Number of failed actions
		int _failed;

	public:
		Section(const std::string &name, const std::vector<Action> &commands);
		~Section();

		std::string name() const;
		int successful() const;
		int failed() const;

		void run_actions();
	};

} // namespace dyt

#endif // SECTION_H