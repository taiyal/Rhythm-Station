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

void IniParser::Load(std::string _path)
{
	std::string current_section = "";
	_path = FileManager::GetFile(_path);
	std::string file_contents = FileManager::GetFileContents(_path);

	std::vector<std::string> lines = split(file_contents, '\n');
	for(unsigned i = 0; i<lines.size(); i++)
	{
		std::string line = lines[i];
		if(line[0] == '[' && line[line.size()-1] == ']')
			current_section = line.substr(1,line.size()-2);
		if(!current_section.empty())
		{
			std::vector<std::string> vLine = split(lines[i], '=');
			
			// XXX: fixme
			if(vLine.size() > 2)
				Log::Print("Too many =, data after the second will not be read.");
			if(vLine.size() >= 2)
			{
				ini_data[current_section] = std::pair<std::string,std::string> (vLine[0],vLine[1]);
				std::ostringstream str;
				str << "Section: " << current_section;
				str << ", Key: " << vLine[0];
				str << ", Value: " << vLine[1];
				Log::Print(str.str());
			}
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
