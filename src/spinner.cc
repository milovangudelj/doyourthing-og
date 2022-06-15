#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <thread>

#include "Spinner.hh"

using namespace std;
using namespace dyt;

Spinner::Spinner(const std::string &name) : _name{name}, _success{false}, _is_running{false}, _delay{150}
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
	while (_is_running)
	{
		printf(".");
		fflush(stdout);

		std::this_thread::sleep_for(std::chrono::milliseconds(_delay));
	}

	printf(" %s Done.\n", _success ? "✓" : "✗");
}