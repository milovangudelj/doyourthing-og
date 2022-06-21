#include <map>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <fmt/format.h>
#include <fmt/printf.h>
#include "nlohmann/json.hpp"

#include "Manager.hh"
#include "Settings.hh"

using namespace std;
namespace fs = std::filesystem;
using namespace dyt;
using json = nlohmann::json;

string get_homedir()
{
	fs::path home = "/home";
	vector<string> users;

	for (const auto &entry : fs::directory_iterator(home))
	{
		users.push_back(entry.path().string());
	}

	return users.at(0);
}

int main()
{
	if (!system(NULL))
	{
		fmt::printf("Command processor not available...\n");
		exit(EXIT_FAILURE);
	}

	fs::path path_to_config(get_homedir());
	path_to_config /= ".doyourthing/config.json";

	if (!fs::exists(path_to_config))
	{
		fmt::printf("You need to provide a configuration file under %s.\nIf you need an example visit https://github.com/milovangudelj/doyourthing/blob/master/config/config.json\n", path_to_config.string());
		exit(0);
	}

	DoYourThing manager(path_to_config, {{{Settings::SettingName::Quiet, Settings::SettingOption::y}}});

	manager.do_it();

	return 0;
}