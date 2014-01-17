/*
 * main.cpp
 *
 *  Created on: Dec 22, 2013
 *      Author: Jonathan Baltazar
 */

#include <krafter/Engine.h>
#include <iostream>
#include <cstdlib>

using namespace krafter;

int main(int argc, const char *argv[]) {
	std::cout << "Content-Type: text/plain\r\n";
	std::cout << "\r\n";

	Engine engine;
	engine.run();

	std::cout << getenv("LD_LIBRARY_PATH") << "\n\n";
	std::cout << "end\n";

	return 0;
}


