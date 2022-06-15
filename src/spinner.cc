#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <thread>

#include "Spinner.hh"

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

	while (_is_running)
	{
		printf(" %s", _frames.at(frame).c_str());
		fflush(stdout);

		frame++;
		if (frame >= _frames.size())
			frame = 0;

		std::this_thread::sleep_for(std::chrono::milliseconds(_delay));

		printf("\b\b");
		fflush(stdout);
	}

	printf(" %s Done.\n", _success ? "✓" : "✗");
}