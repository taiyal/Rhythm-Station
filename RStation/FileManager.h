#ifndef _File_Manager_H_
#define _File_Manager_H_

#include <string>

namespace FileManager
{
	bool FileExists(std::string);
	void SetWorkingDirectory();
	std::string GetWorkingDirectory();
	std::string GetFile(std::string);
	std::string GetThemeFile(std::string);
}

#endif
