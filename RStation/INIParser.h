#ifndef _INI_PARSER_H_
#define _INI_PARSER_H_

#include "RStation.h"
#include <map>

class IniParser // : public Parser
{
public:
	IniParser() { }
	virtual ~IniParser() { }
	
	void Load(std::string path);
	std::string getKeys();
	std::string getItem(std::string key, std::string name);
private:
	std::map<std::string, std::map<std::string, std::string> > ini_data;
};

#endif
