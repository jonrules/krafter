/*
 * String.h
 *
 *  Created on: Dec 26, 2013
 *      Author: Jonathan Baltazar
 */

#ifndef STRING_H_
#define STRING_H_

#include <sstream>

namespace krafter {

	class String {
		public:
			static const unsigned int FLAG_CONCAT = 1;
			unsigned int flags;
			String();
			String(const String &string);
			String(const char *chars);
			virtual ~String();
			String& append(const char *chars);
			String& append(char c);
			String& append(int integer);
			String& append(unsigned int integer);
			String& append(const String &string);
			unsigned int find(const String &string) const;
			unsigned int length() const;
			String& replace(const char *find, const char *replace);
			String& replace(String &find, String &replace);
			static char* replace(const char *input, unsigned int length, const char *find,
					const char *replace);
			String& reset();
			String& set(const char *chars);
			String& set(char c);
			String& set(int integer);
			String& set(const String &string);
			String serialize();
			const char* toChars() const;
			String& operator= (const char *rhs);
			String& operator= (const String &rhs);
			String& operator+ (const char *rhs);
			String& operator+ (char rhs);
			String& operator+ (int rhs);
			String& operator+ (String &rhs);
			String& operator+= (const char *rhs);
			String& operator+= (char rhs);
			String& operator+= (int rhs);
			String& operator+= (unsigned int rhs);
			String& operator+= (const String &rhs);
			String& operator<< (const char *rhs);
			String& operator<< (char rhs);
			String& operator<< (int rhs);
			String& operator<< (unsigned int rhs);
			String& operator<< (const String &rhs);
			bool operator< (const String &rhs) const;
		private:
			std::stringstream _data;
			std::string _empty;
			mutable char *_chars;
			void init();
	};

} /* namespace krafter */

#endif /* STRING_H_ */
