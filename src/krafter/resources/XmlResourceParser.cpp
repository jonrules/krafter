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
#include <vector>

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
			unsigned int serial = 0;

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
				std::map<String, char> &includes, unsigned int &serial) {
			// Body of source
			String body;
			// Class name of parent element
			String className(parentElement->Value());
			// Add class name to includes
			includes[className]++;
			// Object name of parent element instance
			String objectName = "object";
			objectName << serial;
			// Generate C++ type from class name
			String type = className;
			type.replace(".", "::");
			// Function variables
			std::vector<String> constructorArgs;
			std::vector<String> functionNames;
			std::vector<std::vector<String> > functionArgs;
			// Iteration variables
			TiXmlNode *node, *functionArgNode;
			TiXmlElement *element, *functionArgElement;
			String value;
			unsigned int argSerial, functionCallCount = 0;
			int nodeType, functionArgNodeType;

			// Child parsing loop
			node = parentElement->FirstChild();
			while (node) {
				// Get node type
				nodeType = node->Type();
				// Check node type
				if (nodeType == TiXmlNode::TINYXML_ELEMENT) {
					// Element type indicates one or more functions or constructor arguments
					element = (TiXmlElement*) node;
					// Value is tag name
					value = element->Value();
					// Check if value contains a period (.)
					if (value.find(".") != (unsigned int) -1) {
						// A period indicates a class name as a constructor argument
						// Capture serial for current object
						argSerial = ++serial;
						// Append to constructor args
						constructorArgs.push_back(String("object") << argSerial);
						// Generate argument object source
						body << this->generateSource(element, includes, serial);
					} else {
						// No period indicates no namespace, therefore it is a function name
						functionNames.push_back(value);
						// Parse function arguments
						functionArgNode = element->FirstChild();
						while (functionArgNode) {
							if (functionCallCount + 1 > functionArgs.size()) {
								std::vector<String> args;
								functionArgs.push_back(args);
							}
							functionArgNodeType = functionArgNode->Type();
							if (functionArgNodeType == TiXmlNode::TINYXML_ELEMENT) {
								functionArgElement = (TiXmlElement*) functionArgNode;
								// Capture serial for current object
								argSerial = ++serial;
								// Append to function args
								String argObjectName = String("object") << argSerial;
								functionArgs[functionCallCount].push_back(argObjectName);
								// Generate argument source
								body << this->generateSource(functionArgElement, includes, serial);
							} else if (functionArgNodeType == TiXmlNode::TINYXML_TEXT) {
								String functionArgValue = functionArgNode->Value();
								functionArgs[functionCallCount].push_back(
									functionArgValue.serialize()
								);
							}
							// Iterate next sibling
							functionArgNode = functionArgNode->NextSibling();
						}
						functionCallCount++;
					}
				} else if (nodeType == TiXmlNode::TINYXML_TEXT) {
					// Text type indicates a single string argument for the constructor
					value = node->Value();
					constructorArgs.push_back(value.serialize());
				}
				// Iterate next sibling
				node = node->NextSibling();
			}
			// Generate constructor
			body << type << ' ' << objectName;
			unsigned int constructorArgsSize = constructorArgs.size();
			if (constructorArgsSize > 0) {
				body  << '(';
				for (unsigned int a = 0; a < constructorArgsSize; a++) {
					if (a > 0) {
						body << ',';
					}
					body << constructorArgs[a];
				}
				body << ')';
			}
			body << ";\n";
			// Generate function calls
			for (unsigned int n = 0; n < functionNames.size(); n++) {
				body << objectName << '.' << functionNames[n] << '(';
				for (unsigned int a = 0; a < functionArgs[n].size(); a++) {
					if (a > 0) {
						body << ',';
					}
					body << functionArgs[n][a];
				}
				body << ");\n";
			}

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
