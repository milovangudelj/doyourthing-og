#include <iostream>
#include <fstream>
#include <stdio.h>

#include "nlohmann/json.hpp"

#include "libdyt.hh"

using namespace std;
using namespace dyt;

DoYourThing::DoYourThing(const std::string &path_to_config)
{
	ifstream config(path_to_config);

	config >> _config;

	setup();
}

DoYourThing::DoYourThing(const char *path_to_config) : DoYourThing(std::string(path_to_config))
{
}

DoYourThing::~DoYourThing()
{
}

void DoYourThing::setup()
{
	std::vector<std::string> commands{"dnf -q -y -C module install nodejs:16"};

	Action action("Node.js (npm)", commands);

	std::vector<Action> actions{action};

	Section section("Package managers", actions);

	_sections.push_back(section);
}

void DoYourThing::print_config()
{
	std::cout << std::setw(4) << _config << '\n';
}

void DoYourThing::do_it()
{
	for (auto section : _sections)
	{
		printf("%s...\n\n", section.name().c_str());

		section.run_actions();

		printf(" %d successful\n %d failed\n\n", section.successful(), section.failed());
	}

	theend();
}

void DoYourThing::theend()
{
	printf("* Done! *\n\n");
}