/*
 * IniConfig.h
 *
 *  Created on: Dec 25, 2013
 *      Author: Jonathan Baltazar
 */

#ifndef INICONFIG_H_
#define INICONFIG_H_

#include "Config.h"

namespace krafter {
	namespace config {

		class IniConfig: Config {
			public:
				IniConfig();
				virtual ~IniConfig();
		};

	} /* namespace config */
} /* namespace krafter */

#endif /* INICONFIG_H_ */
