#ifndef _INI_PARSER_H_
#define _INI_PARSER_H_

#include "RStation.h"
#include <map>

class INILoader
{
public:
	void Load(std::string path);
	std::string getKeys();
	std::string getValue(std::string key, std::string name);
private:
	std::map<std::string, std::map<std::string, std::string> > ini_data;
};

#endif
