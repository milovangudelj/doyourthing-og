#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <fmt/printf.h>

#include "Spinner.hh"
#include "Colors.hh"

using namespace std;
using namespace dyt;

Spinner::Spinner(const std::string &name) : _name{name}, _frames{{"⣷", "⣯", "⣟", "⡿", "⢿", "⣻", "⣽", "⣾"}}, _success{false}, _is_running{false}, _delay{150}
{
}

Spinner::~Spinner()
{
}

void Spinner::start()
{
	if (!_is_running)
	{
		_is_running = true;

		printf(" %s ", _name.c_str());
		fflush(stdout);

		_thread = std::thread(&Spinner::spin, this);
	}
}

void Spinner::stop(bool success)
{
	_is_running = false;
	_success = success;
	_thread.join();
}

void Spinner::spin()
{
	int frame = 0;
	Colors &colors = Colors::Get();

	while (_is_running)
	{
		fmt::printf("\r%s %s %s", colors.ERASE_E, colors.paint(_frames.at(frame), colors.BLUE_FG), colors.paint(_name, colors.BRIGHT));
		fflush(stdout);

		frame++;
		if (frame >= _frames.size())
			frame = 0;

		std::this_thread::sleep_for(std::chrono::milliseconds(_delay));
	}

	fmt::printf("\r %s %s\n", _success ? colors.paint("✓", colors.GREEN_FG) : colors.paint("✗", colors.RED_FG), colors.paint(_name, colors.BRIGHT));
}