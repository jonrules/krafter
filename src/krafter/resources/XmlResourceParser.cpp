/*
 * XmlResourceParser.cpp
 *
 *  Created on: Dec 25, 2013
 *      Author: Jonathan Baltazar
 */

#include <krafter/resources/XmlResourceParser.h>
#include <krafter/String.h>
#include <map>
#include <tinyxml/tinyxml.h>

namespace krafter {
	namespace resources {

		XmlResourceParser::XmlResourceParser() {
			_doc = NULL;
		}

		XmlResourceParser::~XmlResourceParser() {
			delete _doc;
			_doc = NULL;
		}

		String XmlResourceParser::generateSource() {
			String source;
			if (_doc == NULL || _doc->Error()) {
				return source;
			}

			TiXmlElement *rootElement = _doc->RootElement();
			std::map<String, char> includes;
			int serial = 0;

			String body = this->generateSource(rootElement, includes, serial);

			std::map<String, char>::iterator iter;
			for (iter = includes.begin(); iter != includes.end(); ++iter) {
				String name = iter->first;
				name.replace(".", "/");
				source << "#include <" << name << ".h>\n";
			}
			source << "int main(int argc, const char *argv[]) {\n";
			source << body << "\n";
			if (body.length() > 0) {
				source << "object0.print();\n";
			}
			source << "}";

			return source;
		}

		String XmlResourceParser::generateSource(TiXmlElement *parentElement,
				std::map<String, char> &includes, int &serial) {
			String body;
			String className(parentElement->Value());
			String objectName = "object";
			objectName << serial;

			includes[className]++;
			String type = className;
			type.replace(".", "::");
			body << type << " " << objectName << ";\n";

			TiXmlNode *functionNode, *classNode;
			TiXmlElement *functionElement, *classElement;
			String arg;
			functionNode = parentElement->FirstChild();
			while (functionNode) {
				if (functionNode->Type() == TiXmlNode::TINYXML_ELEMENT) {
					functionElement = (TiXmlElement*) functionNode;
					classNode = functionElement->FirstChild();
					arg.reset();
					while (classNode) {
						switch (classNode->Type()) {
							case TiXmlNode::TINYXML_ELEMENT: {
								classElement = (TiXmlElement*) classNode;
								arg << "object" << (serial + 1);
								body << this->generateSource(classElement, includes, ++serial);
								break;
							}
							case TiXmlNode::TINYXML_TEXT: {
								arg << '"' << classNode->Value() << '"';
								break;
							}
							default: {

							}
						}
						classNode = functionElement->IterateChildren(classNode);
					}
					body << objectName << "." << functionElement->Value();
					body << "(" << arg << ");\n";
				}
				functionNode = parentElement->IterateChildren(functionNode);
			}
//			for (node = parentElement->FirstChild(); node; node = node->NextSibling()) {
//
//			}

			return body;
		}

		void XmlResourceParser::parseFile(const char *filename) {
			delete(_doc);
			_doc = new TiXmlDocument(filename);
			bool loaded = _doc->LoadFile();
			if (!loaded) {
				// Throw exception
			}
		}

		void XmlResourceParser::parseFile(const String &filename) {
			this->parseFile(filename.toChars());
		}

	} /* namespace resources */
} /* namespace krafter */
