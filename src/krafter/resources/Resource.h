/*
 * Resource.h
 *
 *  Created on: Dec 25, 2013
 *      Author: Jonathan Baltazar
 */

#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <krafter/String.h>

namespace krafter {
	namespace resources {

		class Resource {
			public:
				Resource();
				virtual ~Resource();
				void addResource(Resource &resource);
				String getHeader(const char *name);
				String getHeader(String name);
				String getPayload();
				void print();
				void setHeader(const char *header);
				void setHeader(const String header);
				void setPayload(const char *payload);
				void setPayload(const String header);
				String toString();
			private:
				String _payload;
		};

	} /* namespace resources */
} /* namespace krafter */

#endif /* RESOURCE_H_ */
