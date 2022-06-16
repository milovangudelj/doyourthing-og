#include <iostream>
#include <fstream>
#include <stdio.h>
#include <fmt/printf.h>
#include "nlohmann/json.hpp"

#include "Manager.hh"
#include "Colors.hh"

using namespace std;
using namespace dyt;

DoYourThing::DoYourThing(const std::string &path_to_config, const std::string &path_to_defaults)
{
	ifstream config(path_to_config);
	config >> _config;

	ifstream defaults(path_to_defaults);
	defaults >> _defaults;

	setup();
}

DoYourThing::DoYourThing(const char *path_to_config, const char *path_to_defaults) : DoYourThing(std::string(path_to_config), std::string(path_to_defaults))
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

void DoYourThing::print_defaults()
{
	std::cout << std::setw(4) << _defaults << '\n';
}

void DoYourThing::do_it()
{
	Colors &colors = Colors::Get();

	for (auto &section : _sections)
	{
		printf("%s...\n\n", section.name().c_str());

		section.run_actions();
	}

	theend();
}

void DoYourThing::theend()
{
	Colors &colors = Colors::Get();

	printf("\n* Done! *\n\n"); // TODO: Add gradient

	for (auto &section : _sections)
	{
		fmt::printf("%s:\n %s successful\n %s failed\n\n", section.name(), colors.paint(section.successful(), colors.GREEN_FG), colors.paint(section.failed(), colors.RED_FG));
	}
}