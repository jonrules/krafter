/*
 * File.h
 *
 *  Created on: Jan 16, 2014
 *      Author: Jonathan Baltazar
 */

#ifndef FILE_H_
#define FILE_H_

#include <krafter/String.h>
#include <fstream>

namespace krafter {
	namespace server {

		class File {
			public:
				File();
				virtual ~File();
				void close();
				static String getParentFolder(const String &filename);
				void open(const String &filename);
				void open(const String &filename, std::ios::openmode mode);
				void openRead(const String &filename, bool binary);
				void openWrite(const String &filename, bool binary);
				String& read(String &string, unsigned int size);
				void write(const String &string);
				File& operator<< (const String &rhs);
			private:
				String _filename;
				std::fstream _fileStream;
		};

	} /* namespace server */
} /* namespace krafter */

#endif /* FILE_H_ */
