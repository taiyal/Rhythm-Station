#include "RStation.h"
#include <GL/glfw.h>
#include "MouseHandler.h"
#include "InputManager.h"
#include "SceneManager.h"

struct v2int{ int x, y, cx, cy; };

MouseInfo Mouse;
v2int screenSize;

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
	// messy
	if(_x > screenSize.cx)
		_x = screenSize.cx;
	else if (_x < -screenSize.cx)
		_x = -screenSize.cx;

	if(_y > screenSize.cy)
		_y = screenSize.cy;
	else if (_y < -screenSize.cy)
		_y = -screenSize.cy;
	
	glfwSetMousePos(_x,_y);
	
	Mouse.x = _x;
	Mouse.y = _y;
	Mouse.moving = true;
		
	SendMouseInput();
}

void RegisterMouseCallbacks()
{
	glfwGetWindowSize(&screenSize.x, &screenSize.y);
	screenSize.cx = screenSize.x/2;
	screenSize.cy = screenSize.y/2;
	
	glfwSetMouseButtonCallback(MouseButtonCallback);
	glfwSetMousePosCallback(MousePosCallback);
	Log::Print("Registered MouseHandler.");
}
