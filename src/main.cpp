/*
 * main.cpp
 *
 *  Created on: Dec 22, 2013
 *      Author: Jonathan Baltazar
 */

#include <iostream>
#include <string>
#include <krafter/resources/XmlResourceParser.h>
#include <krafter/String.h>
#include <cstdlib>
using namespace krafter;

int main(int argc, const char *argv[]) {
	// Headers
	std::cout << "Content-Type: text/plain; charset=utf-8\r\n";
	std::cout << "\r\n";

	// Document root
	char *documentRoot = getenv("DOCUMENT_ROOT");
	std::cout << "DOCUMENT_ROOT: " << documentRoot << "\n\n";

	// Resource
	String resourceFilename = documentRoot;
	resourceFilename << "/www/text.kraft";
	resources::XmlResourceParser parser;
	parser.parseFile(resourceFilename);
	std::cout << "resourceFilename: " << resourceFilename.toChars() << "\n\n";
	String source = parser.generateSource();
	std::cout << "Source:\n" << source.toChars() << "\n";

	return 0;
}


