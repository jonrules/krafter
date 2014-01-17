/*
 * Engine.cpp
 *
 *  Created on: Jan 16, 2014
 *      Author: Jonathan Baltazar
 */

#include <krafter/Engine.h>
#include <krafter/resources/XmlResourceParser.h>
#include <krafter/String.h>
#include <krafter/server/File.h>
#include <iostream>
#include <cstdlib>

namespace krafter {

	Engine::Engine() {
		// TODO Auto-generated constructor stub

	}

	Engine::~Engine() {
		// TODO Auto-generated destructor stub
	}

	void Engine::run() {
		// Environment variables
		String documentRoot = getenv("DOCUMENT_ROOT");
		String requestUri = getenv("REQUEST_URI");

		// Build resource filename
		String resourceFilename;
		resourceFilename << documentRoot << "/www" << requestUri << ".kraft";

		// Build output source filename
		String outputSrcFilename;
		outputSrcFilename << documentRoot << "/src/www" << requestUri << ".cpp";
		std::cout << outputSrcFilename.toChars() << "\n";

		// Build output binary filename
		String outputBinFilename;
		outputBinFilename << documentRoot << "/bin/www" << requestUri;
		std::cout << outputBinFilename.toChars() << "\n";

		// Parse resource
		resources::XmlResourceParser parser;
		parser.parseFile(resourceFilename);

		// Generate resource source code
		String source = parser.generateSource();
		if (source.length() < 1) return;

		// Make source directories
		String parentSrcFolder = server::File::getParentFolder(outputSrcFilename);
		String mkCmd("mkdir -p ");
		mkCmd << parentSrcFolder;
		std::cout << mkCmd.toChars() << "\n";
		system(mkCmd.toChars());
		// Write source file
		server::File outputSrcFile;
		outputSrcFile.openWrite(outputSrcFilename, false);
		outputSrcFile << source;
		outputSrcFile.close();

		// Make binary directories
		String parentBinFolder = server::File::getParentFolder(outputBinFilename);
		mkCmd = "mkdir -p ";
		mkCmd << parentBinFolder;
		std::cout << mkCmd.toChars() << "\n";
		system(mkCmd.toChars());
		// Make binaries
		String binCmd("g++ -Wall");
		binCmd << " -L" << documentRoot << "/bin";
		binCmd << " -I" << documentRoot << "/include";
		binCmd << " -o " << outputBinFilename;
		binCmd << " " << outputSrcFilename;
		binCmd << " -lkrafter";
		std::cout << binCmd.toChars() << "\n";
		system(binCmd.toChars());
	}

} /* namespace krafter */
