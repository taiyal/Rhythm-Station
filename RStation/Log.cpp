#include "Log.h"
#include "FileManager.h"
#include <fstream>

using namespace std;

fstream logFile;

void Log::Open()
{
	string file = FileManager::GetFile("RStation-log.txt");
	logFile.open(file.c_str(), fstream::out);
	Print("Starting RStation");
	Print("--------------------------------------------");
}

void Log::Close()
{
	logFile.close();
}

void Log::DebugPrint(std::string input)
{
#if _DEBUG_
	Print(input);
#endif
}

void Log::Print(std::string input)
{
	input += "\n";
	cout << input;
	logFile << input;
}	
