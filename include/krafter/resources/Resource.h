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
				virtual String getHeader(const String &name);
				virtual String getHeaders();
				virtual String getPayload();
				virtual void print();
				virtual void setHeader(const String &name, const String &value);
				virtual void setPayload(const String &payload);
				virtual String toString();
			private:
				std::map<String, String> _headers;
				String _payload;
		};

	} /* namespace resources */
} /* namespace krafter */

#endif /* RESOURCE_H_ */
