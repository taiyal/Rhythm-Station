#ifndef _RSFILE_H_
#define _RSFILE_H_

#include "RStation.h"

// TODO: Do this right. It's only useful for text files in this state.
class RSFile
{
	RSFile(std::string _path = "");
	~RSFile();
	
	std::string Load(std::string _path);
	std::string Read(std::string _path);
};

#endif