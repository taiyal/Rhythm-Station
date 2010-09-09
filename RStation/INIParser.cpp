#include "IniParser.h"
#include "FileManager.h"

std::vector<std::string> split(std::string &str, char delim)
{
	std::vector<std::string> elems;
	std::stringstream ss(str);
	std::string item;
	while(std::getline(ss, item, delim))
		elems.push_back(item);
	return elems;
}
typedef std::pair<std::string,std::string> sPair;
void IniParser::Load(std::string _path)
{
	std::string current_section = "";
	_path = FileManager::GetFile(_path);
	std::string file_contents = FileManager::GetFileContents(_path);

	std::vector<std::string> lines = split(file_contents, '\n');
	for(unsigned i = 0; i<lines.size(); i++)
	{
		std::string line = lines[i];
		if(line[0] == '[' && line[sizeof(line)-1] == ']');
			current_section = line;
		if(current_section != "")
		{
			std::vector<std::string> vLine = split(lines[i], '=');
			if(vLine[0] != "" && vLine[1] != "")
				ini_data.insert(current_section, sPair(vLine[0],vLine[1]));
		}
	}
}

std::string* IniParser::getKeys()
{
	return NULL;
}

std::string* IniParser::getItem(std::string key, std::string name)
{
	return NULL;
}
