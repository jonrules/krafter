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

		String Resource::getHeader(const char *name) {
			return "";
		}

		String Resource::getHeader(String name) {
			return "";
		}

		String Resource::getPayload() {
			return _payload;
		}

		void Resource::print() {
			String string = this->toString();
			std::cout << string.toChars();
		}

		void Resource::setHeader(const char *header) {

		}

		void Resource::setHeader(const String header) {

		}

		void Resource::setPayload(const char *payload) {
			_payload.set(payload);
		}

		void Resource::setPayload(const String payload) {
			this->setPayload(payload.toChars());
		}

		String Resource::toString() {
			return _payload;
		}

	} /* namespace resources */
} /* namespace krafter */
