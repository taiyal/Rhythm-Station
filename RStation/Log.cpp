#include "Log.h"
#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <GL/glfw.h>
#include <stdint.h>

std::fstream logFile;

void Log::Open()
{
	std::string file = FileManager::GetFile("RStation-log.txt");
	logFile.open(file.c_str(), std::fstream::out);
	Print("Starting RStation");
	Print("-------------------------------------------------------");
}

void Log::Close()
{
	logFile.close();
}

// don't forget to define _DEBUG_!
void Log::DebugPrint(std::string input)
{
#if _DEBUG_
	Print(input+std::string(" (debug)"));
#endif
}

void Log::Print(std::string input)
{
	std::ostringstream out;
	out << "[";
	char buf[16];
	sprintf(buf, "%0.3f", glfwGetTime());
	out << buf;
	out << "] ";
	out << input;
	out << "\n";
	
	std::cout << out.str();
	logFile << out.str();
}	
