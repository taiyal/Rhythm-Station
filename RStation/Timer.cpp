#include "Timer.h"
#include <GL/glfw.h>
#include <sstream>

/*
 * Todo: call glfwGetTime less often in favor of updating by adding frame delta times
 * from the main loop
*/
Timer::Timer() : start_time(glfwGetTime())
{}

void Timer::setTime()
{
	start_time = glfwGetTime();
}

double Timer::Ago()
{
	return glfwGetTime() - start_time;
}

std::string Timer::strAgo()
{
	std::ostringstream str;
	str << this->Ago();
	return str.str();
}
