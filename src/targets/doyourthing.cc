#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

int main()
{
	int i;

	if (!system(NULL))
	{
		printf("Command processor not available...\n");
		exit(EXIT_FAILURE);
	}

	printf("Executing command DIR...\n");

	i = system("dir");

	printf("The value returned was: %d.\n", i);

	ifstream config("config.json");
	json j;
	config >> j;

	// pretty print with indent of 4 spaces
	std::cout << std::setw(4) << j << '\n';

	return 0;
}