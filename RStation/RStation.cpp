#include <GL/glew.h>
#include <GL/glfw.h>
#include "RStation.h"
#include "GameLoop.h"
#include "Log.h"
#include "KeyboardHandler.h"
#include "MouseHandler.h"
#include "Callbacks.h" // not shared.

void InitWindow(int ScrX, int ScrY)
{
	glfwInit();
	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
	glfwOpenWindow(ScrX,ScrY, /* rgba */ 0,0,0,8, /* depth, stencil, mode */ 32,1, GLFW_WINDOW);
	
	// The window title will be overridden less than a second from startup anyways.
	glfwSetWindowTitle("RStation");
	glfwSwapInterval(1);
	glfwDisable(GLFW_AUTO_POLL_EVENTS);
	
	RegisterResizeCallback();
	RegisterKeyboardCallbacks();
	RegisterMouseCallbacks();
}

// TODO: handle command line args for windows and unix
#ifdef _WIN32
int WINAPI WinMain(HINSTANCE d1, HINSTANCE d2, LPSTR d3, int d4)
#else
int main(int argc, char** argv)
#endif
{
	// Init everything needed
	Log::Open();
	
	InitWindow(854, 480); // TODO: read prefs.
	
	/*
	 * Shader support is required as I would like this to be fairly modern.
	 * As my laptop doesn't support OpenGL 3.x and far more hardware is around
	 * which supports 2.x anyways, 2.x will be the base.
	 *
	 * Most hardware which supports it should have enough power to handle this app.
	 * (Excluding some bottom end cards - I don't have high hopes for, say, a GF 6150)
	 */
	glewInit();
	if (!GLEW_VERSION_2_0)
	{
		Log::Print("OpenGL 2.0 is not supported. You may need to update your drivers.");
		return 1;
	}
	
	// Set up our defaults and pass control.
	SetInitialStates();
	Game::Run();
	
	// Clean up
	glfwTerminate();
	Log::Close();
	return 0;
}
