/*
 * Resource.h
 *
 *  Created on: Dec 25, 2013
 *      Author: Jonathan Baltazar
 */

#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <krafter/String.h>
#include <map>

namespace krafter {
	namespace resources {

		class Resource {
			public:
				Resource();
				virtual ~Resource();
				void addResource(Resource &resource);
				String getHeader(const String &name);
				String getPayload();
				void print();
				void setHeader(const String &name, const String &value);
				void setPayload(const String &payload);
				String toString();
			private:
				std::map<String, String> _headers;
				String _payload;
		};

	} /* namespace resources */
} /* namespace krafter */

#endif /* RESOURCE_H_ */
