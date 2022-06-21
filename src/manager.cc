#include <filesystem>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <fmt/printf.h>
#include "nlohmann/json.hpp"

#include "Manager.hh"
#include "Settings.hh"
#include "Colors.hh"

using namespace std;
namespace fs = std::filesystem;
using namespace dyt;
using json = nlohmann::json;

DoYourThing::DoYourThing(const string &path_to_config, const Settings &settings) : _settings{settings}
{
	ifstream config(path_to_config);
	config >> _config;

	auto machine = _config["machines"].get<json::array_t>().at(0);

	_machine_name = machine["name"].get<string>();

	string path_to_defaults = "/opt/DoYourThing/config/defaults.json";
	try
	{
		string custom_defaults = machine["defaults"].get<string>();

		if (custom_defaults.compare("") != 0 && fs::exists(fs::path{custom_defaults}))
		{
			path_to_defaults = custom_defaults;
		}
	}
	catch (const std::exception &e)
	{
		// No custom defaults defined
	}

	ifstream defaults(path_to_defaults);
	defaults >> _defaults;

	setup();
}

DoYourThing::DoYourThing(const char *path_to_config, const Settings &settings) : DoYourThing(string(path_to_config), settings)
{
}

DoYourThing::~DoYourThing()
{
}

void DoYourThing::setup()
{
	auto machine = _config["machines"].get<json::array_t>().at(0);

	auto sections = machine["sections"].get<json::array_t>();

	for (auto section : sections)
	{
		if (section["id"].get<string>().compare("repos") == 0)
		{
			setup_repos(section);
			continue;
		}
		if (section["id"].get<string>().compare("managers") == 0)
		{
			setup_managers(section);
			continue;
		}

		_sections.push_back({section["name"].get<string>(), get_actions(section)});
	}
}

void DoYourThing::setup_repos(const json &section)
{
	vector<Action> actions;

	for (string r : section["actions"].get<vector<string>>())
	{
		auto repo = _defaults["repos"][r].get<json::object_t>();

		auto name = repo["name"].get<string>();
		auto commands = repo["commands"].get<vector<string>>();

		actions.push_back({name, commands});
	}

	_sections.push_back({section["name"].get<string>(), actions});
}

void DoYourThing::setup_managers(const json &section)
{
	vector<Action> actions;

	for (string m : section["actions"].get<vector<string>>())
	{
		auto repo = _defaults["managers"][m].get<json::object_t>();

		auto name = repo["name"].get<string>();
		auto commands = repo["commands"].get<vector<string>>();

		actions.push_back({name, commands});
	}

	_sections.push_back({section["name"].get<string>(), actions});
}

vector<Action> DoYourThing::get_actions(const json &section)
{
	vector<Action> actions;

	for (auto action : section["actions"].get<json::array_t>())
	{
		auto name = action["name"].get<string>();
		auto commands = action["commands"].get<vector<string>>();

		actions.push_back({name, commands});
	}

	return actions;
}

void one_command_test(vector<Section> &sections)
{
	vector<string> commands{"dnf -q -y -C module install nodejs:16"};

	Action action("Node.js (npm)", commands);

	vector<Action> actions{action};

	Section section("Package managers", actions);

	sections.push_back(section);

	Colors &colors = Colors::Get();

	for (auto &section : sections)
	{
		printf("%s...\n\n", section.name().c_str());

		section.run_actions();
	}
}

void DoYourThing::print_config()
{
	cout << setw(3) << _config << '\n';
}

void DoYourThing::print_defaults()
{
	cout << setw(3) << _defaults << '\n';
}

void DoYourThing::do_it()
{
	Colors &colors = Colors::Get();

	fmt::printf("Setting up packages and configurations for machine: %s\n", colors.paint(_machine_name, colors.BRIGHT));

	// Test Section/Action/Spinner functionality with a simple command
	// one_command_test(_sections);

	for (auto &section : _sections)
	{
		printf("\n%s...\n\n", section.name().c_str());

		section.run_actions();
	}

	theend();
}

void DoYourThing::theend()
{
	Colors &colors = Colors::Get();

	printf("\n* Done! *\n\n"); // TODO: Add gradient

	if (_settings[Settings::SettingName::Quiet] == Settings::SettingOption::n)
	{
		for (auto &section : _sections)
		{
			fmt::printf("%s:\n %s successful\n %s failed\n\n", section.name(), colors.paint(section.successful(), colors.GREEN_FG), colors.paint(section.failed(), colors.RED_FG));
		}
	}
}