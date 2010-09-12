#include "RStation.h"
#include <GL/glfw.h>
#include "RSUtil.h"
#include <sstream>

using namespace std;

void Util::UpdateWindowTitle(float delta)
{
	double fps = 1.f / delta;

	ostringstream str;
	str << "RStation - ";
	str << "FPS: ";
	str << int(fps * 10) * 0.1f;
	str << ", Delta: ";
	str << delta;

	string sfps = str.str(); // str.c_str doesn't work?
	glfwSetWindowTitle(sfps.c_str());
}

vector<string> Util::Split(string &str, char delim)
{
	vector<string> elems;
	stringstream ss(str);
	string item;
	while(getline(ss, item, delim))
		elems.push_back(item);
	return elems;
}
