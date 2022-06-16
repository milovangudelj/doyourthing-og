#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "nlohmann/json.hpp"

#include "Manager.hh"

using namespace std;
using namespace dyt;
using json = nlohmann::json;

int main()
{
	if (!system(NULL))
	{
		printf("Command processor not available...\n");
		exit(EXIT_FAILURE);
	}

	DoYourThing manager("config.json", "defaults.json");

	// manager.print_config();
	// manager.print_defaults();
	manager.do_it();

	return 0;
}