#include <GL/glew.h>
#include <GL/glfw.h>
#include "RStation.h"
#include "Log.h"
#include "GameLoop.h"
#include "KeyboardHandler.h"
#include "MouseHandler.h"
#include "AudioManager.h"
#include "INILoader.h"
#include "MathUtils.h"
#include "LuaManager.h"

INILoader* ini = new INILoader();

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
	
	// (re)register mouse callback.
	RegisterMouseCallbacks();
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

void InitWindow(int _width, int _height)
{
	glfwInit();
	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 0);
	glfwOpenWindow(_width, _height, /* rgba */ 0,0,0,8, /* depth, stencil, mode */ 32,1, GLFW_WINDOW);
	glewInit();

	// The window title will be overridden less than a second from startup anyways.
	glfwSetWindowTitle("RStation");
	glfwDisable(GLFW_AUTO_POLL_EVENTS);
	glfwDisable(GLFW_MOUSE_CURSOR);

	int vsync = atoi(ini->getValue("Preferences","VSync").c_str());
	vsync = vsync ? 1 : 0;
	glfwSwapInterval(vsync); // vsync

	glfwSetWindowSizeCallback(ResizeViewport);
	RegisterKeyboardCallbacks();
}

// TODO: handle command line args for windows and unix
#ifdef _WIN32
int WINAPI WinMain(HINSTANCE d1, HINSTANCE d2, LPSTR d3, int d4)
#else
int main(int argc, char** argv)
#endif
{
	// initialize everything needed
	Log::Open();
	Audio::Open();

	ini->Load("GameData/Preferences.ini");
	
	// get the resolution from prefs
	int width = 854;
	int height = 480;

	width = atoi(ini->getValue("Preferences","DisplayWidth").c_str());
	height = atoi(ini->getValue("Preferences","DisplayHeight").c_str());
	
	InitWindow(width, height);
	
	// we're done reading the ini, nuke it.
	delete ini;
	
	/*
	 * Shaders are used for a lot here, so of course OpenGL 2.0 is required.
	 * In the future I may start using Cg, although I like GLSL more it would allow
	 * having a DX renderer without a ton of dupe shaders.
	 */
	if (!GLEW_VERSION_2_0)
	{
		Log::Print("OpenGL 2.0 is not supported. You may need to update your drivers.");
		return 1;
	}

	lua_testLoad();

	// Set up our defaults and pass control.
	SetInitialStates();
	Game::Run();

	// Clean up
	glfwTerminate();
	Audio::Close();
	Log::Close();
	return 0;
}
