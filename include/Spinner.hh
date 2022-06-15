#ifndef SPINNER_H
#define SPINNER_H

#include <vector>
#include <string>
#include <thread>

namespace dyt
{

	/**
	 * @brief Class representing a Spinner
	 *
	 */
	class Spinner
	{
	private:
		/// The name of the Spinner
		std::string _name;
		std::vector<std::string> _frames;
		bool _success;
		bool _is_running;
		int _delay;
		std::thread _thread;

		void spin();

	public:
		Spinner(const std::string &name);
		~Spinner();

		void start();
		void stop(bool success);
	};

} // namespace dyt

#endif // SPINNER_H