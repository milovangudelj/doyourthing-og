#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "nlohmann/json.hpp"

#include "libdyt.hh"

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

	DoYourThing dyter("config.json");

	// dyter.print_config();
	dyter.do_it();

	return 0;
}