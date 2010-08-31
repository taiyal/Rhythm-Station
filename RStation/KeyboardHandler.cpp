#include "KeyboardHandler.h"
#include "SceneManager.h"

int Keys[GLFW_KEY_LAST] = { RS_FIRST_PRESS };

void KeyCallback(int key, int action)
{
	switch ( action )
	{
	case GLFW_PRESS:
		if ( Keys[key] == RS_FIRST_PRESS )
			Keys[key] = RS_HELD;
		else
			Keys[key] = RS_FIRST_PRESS;
		break;
	case GLFW_RELEASE:
		if ( Keys[key] == RS_HELD || Keys[key] == RS_FIRST_PRESS )
			Keys[key] = RS_LET_GO;
		else
			Keys[key] = RS_NONE;
		break;
	}

	IEvent event;
	event.Key = key;
	event.State = Keys[key];

	Scene::SendInput(event);
}

void RegisterKeyboardCallbacks()
{
	glfwSetKeyCallback(KeyCallback);
	Log::Print("Registered KeyboardHandler.");
}
