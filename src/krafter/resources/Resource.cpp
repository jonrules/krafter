/*
 * Resource.cpp
 *
 *  Created on: Dec 25, 2013
 *      Author: Jonathan Baltazar
 */

#include <krafter/resources/Resource.h>
#include <krafter/String.h>
#include <iostream>

namespace krafter {
	namespace resources {

		Resource::Resource() {
			// TODO Auto-generated constructor stub

		}

		Resource::~Resource() {
			// TODO Auto-generated destructor stub
		}

		void Resource::addResource(Resource &resource) {

		}

		String Resource::getHeader(const String &name) {
			return _headers[name];
		}

		String Resource::getPayload() {
			return _payload;
		}

		void Resource::print() {
			String string = this->toString();
			std::cout << string.toChars();
		}

		void Resource::setHeader(const String &name, const String &value) {
			_headers[name] = value;
		}

		void Resource::setPayload(const String &payload) {
			_payload.set(payload);
		}

		String Resource::toString() {
			String string;

			// Headers
			std::map<String, String>::iterator headerIter;
			for (headerIter = _headers.begin(); headerIter != _headers.end(); ++headerIter) {
				string << headerIter->first << ": " << headerIter->second << "\r\n";
			}
			string << "\r\n";

			// Payload
			string << _payload;

			return string;
		}

	} /* namespace resources */
} /* namespace krafter */
