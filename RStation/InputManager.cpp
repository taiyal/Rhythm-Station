#include "RStation.h"
#include "InputManager.h"
#include "MouseHandler.h"
#include "KeyboardHandler.h"

InputManager::InputManager()
{
	// xxx
}

void InputManager::Update()
{
//	Log::Print("Updating input");
	glfwPollEvents();
}
