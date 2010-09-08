#include "RStation.h"
#include <GL/glfw.h>
#include "MouseHandler.h"
#include "InputManager.h"
#include "SceneManager.h"

MouseInfo Mouse;

void SendMouseInput()
{
	IEvent event;
	event.Mouse = Mouse;
	
	Scene::SendInput(event);
}

void MouseButtonCallback(int button, int action)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
		Mouse.left = (action == GLFW_PRESS);
	else if (button == GLFW_MOUSE_BUTTON_RIGHT)
		Mouse.right = (action == GLFW_PRESS);      
	else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
		Mouse.middle = (action == GLFW_PRESS);
	
	SendMouseInput();
}

void MousePosCallback(int _x, int _y)
{
	Mouse.x = _x;
	Mouse.y = _y;
	Mouse.moving = true;
	
	SendMouseInput();
}

void RegisterMouseCallbacks()
{
	glfwSetMouseButtonCallback(MouseButtonCallback);
	glfwSetMousePosCallback(MousePosCallback);
	Log::Print("Registered MouseHandler.");
}
