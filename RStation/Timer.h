#ifndef _Timer_H_
#define _Timer_H_

#include "RStation.h"

class Timer
{
private:
	double start_time;
	void setTime();
public:
	Timer();
	void Touch() { setTime(); }
	double Ago();
	std::string strAgo();
};

#endif
