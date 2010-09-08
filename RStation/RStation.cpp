#include <GL/glew.h>
#include <GL/glfw.h>
#include "RStation.h"
#include "GameLoop.h"
#include "Log.h"
#include "KeyboardHandler.h"
#include "MouseHandler.h"
#include "TextureManager.h"

void GLFWCALL ResizeViewport(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);
	
	// half width, half height.
	int hw, hh;
	hw = int(w*0.5f);
	hh = int(h*0.5f);
	
	glOrtho(-hw, hw, hh, -hh, -hw, hw);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// the frame buffer is usually full of junk after resize. clear it.
	glClear(GL_COLOR_BUFFER_BIT);
}

void SetInitialStates()
{
	glClearColor(0,0,0,1);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_LIGHTING);
}

void InitWindow(int ScrX, int ScrY)
{
	glfwInit();
	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 0);
	glfwOpenWindow(ScrX,ScrY, /* rgba */ 0,0,0,8, /* depth, stencil, mode */ 32,1, GLFW_WINDOW);

	// The window title will be overridden less than a second from startup anyways.
	glfwSetWindowTitle("RStation");
	glfwDisable(GLFW_AUTO_POLL_EVENTS);
//	glfwDisable(GLFW_MOUSE_CURSOR);

	glfwSwapInterval(1); // vsync

	glfwSetWindowSizeCallback(ResizeViewport);
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
