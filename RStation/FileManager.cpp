#include "FileManager.h"
#include "Log.h"

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif

#ifdef __WINDOWS__
#include <direct.h>
#endif

// prevent visual studio warning
#ifdef _MSC_VER
	#define getcwd _getcwd
#endif

#include <stdio.h>
#include <fstream>

namespace FileManager
{
	bool FileExists(std::string _file)
	{
		std::fstream filename;
		filename.open(_file.c_str());
		bool ret = filename.is_open();
		filename.close();
		return ret;
	}
	void SetWorkingDirectory()
	{
// gross
#ifdef __APPLE__
		/*
		 * This function will locate the path to our application on OS X,
		 * unlike windows you cannot rely on the current working directory
		 * for locating your configuration files and resources.
		 */
		char path[1024];
		CFBundleRef mainBundle = CFBundleGetMainBundle();
		assert( mainBundle ); // make sure nothing is terribly wrong here.
		CFURLRef mainBundleURL = CFBundleCopyBundleURL( mainBundle );
		CFStringRef cfStringRef = CFURLCopyFileSystemPath( mainBundleURL, kCFURLPOSIXPathStyle );
		CFStringGetCString( cfStringRef, path, 1024, kCFStringEncodingUTF8 );
		CFRelease( mainBundleURL );
		CFRelease( cfStringRef );
		std::string _path = std::string(path) + "/../";
		chdir(_path.c_str());
#endif
	}
	std::string GetWorkingDirectory()
	{
		SetWorkingDirectory();
		char path[1024];
		getcwd(path, 1024);
		return std::string(path) + "/";
	}
	std::string GetFile(std::string _path)
	{
		return GetWorkingDirectory() + _path;
	}
	std::string GetFileContents(std::string _path)
	{
		std::string out, buf;
		std::ifstream file(_path.c_str());
		
		if(!file.is_open())
			return std::string();
		
		while(!file.eof())
		{
			getline(file, buf);
			out += buf;
			out += "\n";
		}
		
		return out;
	}
}
