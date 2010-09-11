#include "RStation.h"
#include "InputManager.h"
#include "MouseHandler.h"
#include "KeyboardHandler.h"

void InputManager::Update()
{
	glfwPollEvents();
}
