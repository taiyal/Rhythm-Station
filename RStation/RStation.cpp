#include <GL/glew.h>
#include <GL/glfw.h>
#include "RStation.h"
#include "GameLoop.h"
#include "Log.h"
#include "KeyboardHandler.h"
#include "MouseHandler.h"
#include "TextureManager.h"

#ifdef _WITH_OPENAL_
#include "AudioManager.h"
#endif

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
	glewInit();

	// The window title will be overridden less than a second from startup anyways.
	glfwSetWindowTitle("RStation");
	glfwDisable(GLFW_AUTO_POLL_EVENTS);
	glfwDisable(GLFW_MOUSE_CURSOR);

	glfwSwapInterval(1); // vsync

	glfwSetWindowSizeCallback(ResizeViewport);
	RegisterKeyboardCallbacks();
	RegisterMouseCallbacks();
}

#include <OpenAL/al.h>
#include "MathUtils.h"
#include <math.h>

int sine_wave()
{
	// create the buffers
	SoundData *sound = new SoundData();
	if (alGetError() != AL_NO_ERROR)
		return -1;

	ALsizei size, freq;
	ALvoid *data;

	// wave parameters and buffer size
	unsigned char *sineWave;
	int samples = 16;
	int frequency = 200;
	freq = samples * frequency;
	size = 32000; // 32k buffer
	
	// build the sine wave
	sineWave = new unsigned char[size];
	for (int i = 0; i < size; ++i)
	{
		float x = i * 360.f / (float)samples;
		sineWave[i] = sinf(radf(x))*128+128;
	}
	data = sineWave;
	delete[] sineWave;

	alBufferData(sound->buffer[0], AL_FORMAT_STEREO16, data, size, freq);

	if (alGetError() != AL_NO_ERROR)
		return -2;

	alSourcei(sound->source[0], AL_LOOPING, (ALboolean)true);
	alSourcef(sound->source[0], AL_PITCH, 1.0f);
	alSourcei(sound->source[0], AL_BUFFER, sound->buffer[0]);
	alSourcef(sound->source[0], AL_GAIN, 0.5f); // volume

	alSourcePlay(sound->source[0]);
	
	sound->Register();

	return 0;
}

#include "INIParser.h"

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

	sine_wave();

	IniParser* ini = new IniParser();
	ini->Load("GameData/Test.ini");
	
	// get the resolution from prefs
	int width = 854;
	int height = 480;

	width = atoi(ini->getValue("Preferences","Width").c_str());
	height = atoi(ini->getValue("Preferences","Height").c_str());
	
	// we're done reading the ini, nuke it.
	delete ini;

	InitWindow(width, height);
		
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

	// Set up our defaults and pass control.
	SetInitialStates();
	Game::Run();

	// Clean up
	glfwTerminate();
	Audio::Close();
	Log::Close();
	return 0;
}
