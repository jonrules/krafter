/*
 * XmlResourceParser.h
 *
 *  Created on: Dec 25, 2013
 *      Author: Jonathan Baltazar
 */

#ifndef XMLRESOURCEPARSER_H_
#define XMLRESOURCEPARSER_H_

#include <krafter/String.h>
#include <map>
#include <tinyxml/tinyxml.h>

namespace krafter {
	namespace resources {

		class XmlResourceParser {
			public:
				XmlResourceParser();
				virtual ~XmlResourceParser();
				String generateSource();
				void parseFile(const char *filename);
				void parseFile(const String &filename);
			private:
				TiXmlDocument *_doc;
				String generateSource(TiXmlElement *parentElement,
						std::map<String, char> &includes, int &serial);
		};

	} /* namespace resources */
} /* namespace krafter */

#endif /* XMLRESOURCEPARSER_H_ */
