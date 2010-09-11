#include "RStation.h"
#include "InputManager.h"
#include "MouseHandler.h"
#include "KeyboardHandler.h"
#include "SceneManager.h"

void Input::Update()
{
	glfwPollEvents();
}
