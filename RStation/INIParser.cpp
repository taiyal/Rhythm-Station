#include "IniParser.h"
#include "FileManager.h"

using namespace std;

vector<string> split(string &str, char delim)
{
	vector<string> elems;
	stringstream ss(str);
	string item;
	while(getline(ss, item, delim))
		elems.push_back(item);
	return elems;
}

void IniParser::Load(string _path)
{
	string current_section = "";
	_path = FileManager::GetFile(_path);
	string file_contents = FileManager::GetFileContents(_path);

	vector<string> lines = split(file_contents, '\n');
	for(unsigned i = 0; i<lines.size(); i++)
	{
		string line = lines[i];
		if(line[0] == '[' && line[line.size()-1] == ']')
			current_section = line.substr(1,line.size()-2);
		if(!current_section.empty())
		{
			// TODO: string:find and substr instead.
			vector<string> vLine = split(lines[i], '=');
			
			// XXX: fixme
			if(vLine.size() > 2)
				Log::Print("Too many =, data after the second will not be read.");
			
			if(vLine.size() >= 2)
				ini_data[current_section].insert(pair<string,string>(vLine[0], vLine[1]));
		}
	}
}

string IniParser::getValue(string section, string key)
{
	if(!ini_data[section].empty())
	{
		string data (ini_data[section].find(key)->second);
		return data;
	}
	return string();
}
