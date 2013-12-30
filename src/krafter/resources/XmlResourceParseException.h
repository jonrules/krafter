/*
 * XmlResourceParseException.h
 *
 *  Created on: Dec 25, 2013
 *      Author: Jonathan Baltazar
 */

#ifndef XMLRESOURCEPARSEEXCEPTION_H_
#define XMLRESOURCEPARSEEXCEPTION_H_

#include <exception>

namespace krafter {
	namespace config {

		class XmlResourceParseException: public std::exception {
			public:
				XmlResourceParseException();
				virtual ~XmlResourceParseException() throw();
				virtual const char* what() const throw();
		};

	} /* namespace config */
} /* namespace krafter */

#endif /* XMLRESOURCEPARSEEXCEPTION_H_ */
