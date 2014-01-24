/*
 * File.cpp
 *
 *  Created on: Jan 16, 2014
 *      Author: Jonathan Baltazar
 */

#include <krafter/server/File.h>
#include <krafter/String.h>
#include <fstream>
#include <string>
#include <stdio.h>

namespace krafter {
	namespace server {

		File::File() {

		}

		File::~File() {
			this->close();
		}

		void File::close() {
			_fileStream.close();
		}

		String File::execute(const String &filename) {
			FILE *in;
			char buffer[512];
			unsigned int bufferSize = sizeof(buffer);
			String output;

			if (!(in = popen(filename.toChars(), "r"))) {
				//@TODO throw exception
				return output;
			}

			while (fgets(buffer, bufferSize, in) != NULL) {
				output << buffer;
			}

			pclose(in);

			return output;
		}

		bool File::exists(const String &filename) {
			std::ifstream fstream(filename.toChars());
			return fstream;
		}

		String File::getParentFolder(const String &filename) {
			std::string str = filename.toChars();
			str = str.substr(0, str.find_last_of("/"));
			String folder(str.c_str());
			return folder;
		}

		void File::open(const String &filename) {
			_filename = filename;
			_fileStream.open(filename.toChars());
		}

		void File::open(const String &filename, std::ios::openmode mode) {
			_filename = filename;
			_fileStream.open(filename.toChars(), mode);
		}

		void File::openRead(const String &filename, bool binary) {
			std::ios::openmode mode = std::ios::in;
			if (binary) {
				mode |= std::ios::binary;
			}
			this->open(filename, mode);
		}

		void File::openWrite(const String &filename, bool binary) {
			std::ios::openmode mode = std::ios::out | std::ios::trunc;
			if (binary) {
				mode |= std::ios::binary;
			}
			this->open(filename, mode);
		}

		String& File::read(String &string, unsigned int size) {
			char *buffer = new char[size+1];
			_fileStream.read(buffer, size);
			buffer[size] = '\0';
			string << buffer;
			delete[] buffer;
			return string;
		}

		void File::write(const String &string) {
			_fileStream << string.toChars();
		}

		File& File::operator<< (const String &rhs) {
			this->write(rhs);
			return *this;
		}

	} /* namespace server */
} /* namespace krafter */
