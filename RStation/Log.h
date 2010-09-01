#ifndef _Log_H_
#define _Log_H_

#include <string>
#include <iostream>

namespace Log
{
	void Open();
	void Write();
	void Close();

	void DebugPrint(std::string input);
	void Print(std::string input);
};

#endif
