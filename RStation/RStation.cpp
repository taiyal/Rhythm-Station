#include <GL/glew.h>
#include <GL/glfw.h>
#include "RStation.h"
#include "GameLoop.h"
#include "Log.h"
#include "KeyboardHandler.h"
#include "MouseHandler.h"

void GLFWCALL ResizeViewport(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glViewport(0, 0, w, h);
	glOrtho(int(-(w/2)), int((w/2)), int((h/2)), int(-(h/2)), -10, 10);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// the frame buffer is usually full of junk after resize. clear it.
	glClear(GL_COLOR_BUFFER_BIT);
}

void InitWindow(int ScrX, int ScrY)
{
	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 2);
	glfwOpenWindow(
		ScrX,ScrY,	// res
		0,0,0,8,	// RGBA
		32,1,		// depth, stencil
		GLFW_WINDOW
	);	
	glfwSetWindowTitle("RStation");
	glfwSetWindowSizeCallback(ResizeViewport);
	glfwSwapInterval(1); // vsync
	
	glfwDisable(GLFW_AUTO_POLL_EVENTS);
//	glfwEnable(GLFW_KEY_REPEAT);
	
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
	
	glfwInit();
	
	// This needs to read prefs.
	InitWindow(854, 480);
	glewInit();

	if (!GLEW_VERSION_2_0)
	{
		Log::Print("OpenGL 2.0 is not supported. You may need to update your drivers.");
		return 1; // shaders support is required for RStation.
	}
	// todo: reduce logging in release builds
	// don't forget to define _DEBUG_!
	Log::DebugPrint("[main] Setting initial states.");
	glClearColor(0,0,0,1);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_LIGHTING);
	
	Log::DebugPrint("[main] Passing control to Game::Run.");
	Game::Run();
	
	// Clean up
	glfwTerminate();
	Log::Close();
	return 0;
}
