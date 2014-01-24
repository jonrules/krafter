/*
 * String.cpp
 *
 *  Created on: Dec 26, 2013
 *      Author: Jonathan Baltazar
 */

#include <krafter/String.h>
#include <cstring>
#include <string>

namespace krafter {

	String::String() {
		init();
	}

	String::String(const String &string) {
		init();
		this->set(string);
		if (string.flags & String::FLAG_CONCAT) {
			delete &string;
		}
	}

	String::String(const char *chars) {
		init();
		this->set(chars);
	}

	String::~String() {
		if (_chars != NULL) {
			delete[] _chars;
			_chars = NULL;
		}
	}

	String& String::append(const char *chars) {
		_data << chars;
		return *this;
	}

	String& String::append(char c) {
		_data << c;
		return *this;
	}

	String& String::append(int integer) {
		_data << integer;
		return *this;
	}

	String& String::append(unsigned int integer) {
		_data << integer;
		return *this;
	}

	String& String::append(const String &string) {
		this->append(string.toChars());
		return *this;
	}

	unsigned int String::find(const String &string) const {
		return _data.str().find(string.toChars());
	}

	void String::init() {
		this->flags = 0;
		_chars = NULL;
	}

	unsigned int String::length() const {
		return _data.str().length();
	}

	String& String::reset() {
		this->flags = 0;
		_data.str(_empty);
		_data.clear();
		if (_chars != NULL) {
			delete[] _chars;
			_chars = NULL;
		}
		return *this;
	}

	String& String::set(const char *chars) {
		this->reset();
		_data << chars;
		return *this;
	}

	String& String::set(char c) {
		this->reset();
		_data << c;
		return *this;
	}

	String& String::set(int integer) {
		this->reset();
		_data << integer;
		return *this;
	}

	String& String::set(const String &string) {
		this->set(string.toChars());
		return *this;
	}

	String String::serialize() {
		String serialized = *this;
		serialized.replace("\\", "\\\\").replace("\"", "\\\"");
		serialized = String("\"") << serialized << "\"";
		return serialized;
	}

	String& String::replace(const char *find, const char *replace) {
		char *replaced = String::replace(this->toChars(), this->length(), find, replace);
		this->set(replaced);
		delete[] replaced;
		return *this;
	}

	String& String::replace(String &find, String &replace) {
		return this->replace(find.toChars(), replace.toChars());
	}

	char* String::replace(const char *input, unsigned int length, const char *find,
			const char *replace) {
		unsigned int findLength = strlen(find), replaceLength = strlen(replace);
		unsigned int newLength = length;
		const char *position;
		unsigned int replacements = 0;

		position = strstr(input, find);
		while (position) {
			newLength += (replaceLength - findLength);
			position = strstr(position+1, find);
			replacements++;
		}

		if (replacements > 0) {
			char *output = new char[newLength + 1];
			const char *prevPosition = input - 1;
			unsigned int written = 0, writing = 0;
			position = strstr(input, find);
			while (position) {
				writing = (unsigned int)(position - prevPosition - 1);
				memcpy(output + written, prevPosition + 1, writing);
				written += writing;
				memcpy(output + written, replace, replaceLength);
				written += replaceLength;
				prevPosition = position;
				position = strstr(position + 1, find);
			}
			writing = (input + length) - prevPosition - findLength;
			memcpy(output + written, prevPosition + findLength, writing);
			written += writing;
			output[written] = '\0';
			return output;
		}

		char *output = new char[length+1];
		memcpy(output, input, length);
		output[length] = '\0';
		return output;
	}

	const char* String::toChars() const {
		if (_chars != NULL) {
			delete[] _chars;
		}
		unsigned int length = _data.str().length();
		_chars = new char[length + 1];
		memcpy(_chars, _data.str().c_str(), length);
		_chars[length] = '\0';
		return _chars;
	}

	String& String::operator= (const char *rhs) {
		this->set(rhs);
		return *this;
	}

	String& String::operator= (const String &rhs) {
		if (this == &rhs) {
			return *this;
		}
		this->set(rhs);
		return *this;
	}

	String& String::operator+ (const char *rhs) {
		if (this->flags & String::FLAG_CONCAT) {
			this->append(rhs);
			return *this;
		}

		String *concatString = new String(*this);
		concatString->append(rhs);
		concatString->flags |= String::FLAG_CONCAT;
		return *concatString;
	}

	String& String::operator+ (char rhs) {
		if (this->flags & String::FLAG_CONCAT) {
			this->append(rhs);
			return *this;
		}

		String *concatString = new String(*this);
		concatString->append(rhs);
		concatString->flags |= String::FLAG_CONCAT;
		return *concatString;
	}

	String& String::operator+ (int rhs) {
		if (this->flags & String::FLAG_CONCAT) {
			this->append(rhs);
			return *this;
		}

		String *concatString = new String(*this);
		concatString->append(rhs);
		concatString->flags |= String::FLAG_CONCAT;
		return *concatString;
	}

	String& String::operator+ (String &rhs) {
		if (this->flags & String::FLAG_CONCAT) {
			this->append(rhs);
			return *this;
		}

		String *concatString = new String(*this);
		concatString->append(rhs);
		concatString->flags |= String::FLAG_CONCAT;
		return *concatString;
	}

	String& String::operator+= (const char *rhs) {
		this->append(rhs);
		return *this;
	}

	String& String::operator+= (char rhs) {
		this->append(rhs);
		return *this;
	}

	String& String::operator+= (int rhs) {
		this->append(rhs);
		return *this;
	}

	String& String::operator+= (unsigned int rhs) {
		this->append(rhs);
		return *this;
	}

	String& String::operator+= (const String &rhs) {
		this->append(rhs);
		return *this;
	}

	String& String::operator<< (const char *rhs) {
		return (*this += rhs);
	}

	String& String::operator<< (char rhs) {
		return (*this += rhs);
	}

	String& String::operator<< (int rhs) {
		return (*this += rhs);
	}

	String& String::operator<< (unsigned int rhs) {
		return (*this += rhs);
	}

	String& String::operator<< (const String &rhs) {
		return (*this += rhs);
	}

	bool String::operator< (const String &rhs) const {
		return strcmp(this->toChars(), rhs.toChars());
	}

} /* namespace krafter */
