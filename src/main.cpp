#include <iostream>

#include "rose.h"

int main(int argc, char* argv[]) {
	
	if (argc != 2)
	{
		//std::cout << "Expected file path.";
		//return 1;
	}

	rose::Rose rose;
	return rose.runGame();
}