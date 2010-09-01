#include "RStation.h"
#include <GL/glfw.h>
#include "RSUtil.h"
#include <sstream>

void Util::UpdateWindowTitle(float delta)
{
	double fps = 1.f / delta;

	std::ostringstream str;
	str << "RStation - ";
	str << "FPS: ";
	str << int(fps * 10) * 0.1f;
	str << ", Delta: ";
	str << delta;

	std::string sfps = str.str(); // str.c_str doesn't work?
	glfwSetWindowTitle(sfps.c_str());
}
