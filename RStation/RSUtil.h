#ifndef _RSUTIL_H_
#define _RSUTIL_H_

#include "RStation.h"

namespace Util
{
	void UpdateWindowTitle(float delta);
	std::vector<std::string> Split(std::string &str, char delim);
}

#endif
