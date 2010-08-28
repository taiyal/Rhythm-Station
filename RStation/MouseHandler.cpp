#include "RStation.h"
#include <GL/glfw.h>
#include "MouseHandler.h"

MouseInfo Mouse;

void MouseButtonCallback(int button, int action)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
		Mouse.left = (action == GLFW_PRESS);
	else if (button == GLFW_MOUSE_BUTTON_RIGHT)
		Mouse.right = (action == GLFW_PRESS);      
	else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
		Mouse.middle = (action == GLFW_PRESS);
}

void MousePosCallback(int _x, int _y)
{
	Mouse.x = _x;
	Mouse.y = _y;
}

void RegisterMouseCallbacks()
{
	glfwSetMouseButtonCallback(MouseButtonCallback);
	glfwSetMousePosCallback(MousePosCallback);
	Log::Print("Registered MouseHandler.");
}
