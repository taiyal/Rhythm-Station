#include "INILoader.h"
#include "FileManager.h"
#include "RSUtil.h"

using namespace std;

void INILoader::Load(string _path)
{
	string current_section = "";
	_path = FileManager::GetFile(_path);
	string file_contents = FileManager::GetFileContents(_path);

	vector<string> lines = Util::Split(file_contents, '\n');
	for (unsigned i = 0; i<lines.size(); i++)
	{
		string line = lines[i];
		switch (line[0])
		{
		case '#':	// # comment
		case ';':	// ; comment
			continue;
		case '-':	// -- comment
			if (line[1] == '-')
				continue;
		case '/':	// // comment
			if (line[1] == '/')
				continue;
		default:
			break;
		}
		if (line[0] == '[' && line[line.size()-1] == ']')
			current_section = line.substr(1,line.size()-2);
		if (!current_section.empty())
		{
			size_t pos;
			pos = line.find("=");
			if(pos == string::npos)
				continue;
			string key = line.substr(0,pos);
			string value = line.substr(pos+1,line.size()-1);
			
			ini_data[current_section].insert(pair<string,string>(key, value));
		}
	}
}

//template <class T>
string INILoader::getValue(string section, string key)
{
	if(!ini_data[section].empty())
	{
		if(ini_data[section].find(key) != ini_data[section].end())
			return ini_data[section].find(key)->second;
	}
	return string();
}
