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

#define D2R 0.0174532925
#include <OpenAL/al.h>
#include "MathUtils.h"
#include <math.h>

int sine_wave()
{
	alGetError(); // Clear errors

	ALuint buffer[1];

	// Create the buffers
	alGenBuffers(1, buffer);
	if (alGetError() != AL_NO_ERROR)
		return -1;

	// Build the data
	ALenum format = AL_FORMAT_STEREO16;
	ALsizei size;
	ALsizei freq;
	ALboolean loop;
	ALvoid *data;

	unsigned char *sineWave;
	int samples = 16;
	int frequency = 20;
	loop = true;
	freq = samples * frequency;
	size = freq;
	
	if(!(sineWave = (unsigned char*)malloc(size)))
		return -2;
	
	for (int i = 0; i < size; ++i) {
		float x = i * 360.f / (float)samples;
		sineWave[i] = sinf(radf(x)) * 255;
	}
	data = sineWave;

	alBufferData(buffer[0], format, data, size, freq);
	// Setup sources
	ALuint source[1];
	alGenSources(1, source);
	if (alGetError() != AL_NO_ERROR)
		return -3;

	float srcPos[] = {3.0, 0.0, -3.0};

	alSourcei(source[0], AL_LOOPING, loop);
	alSourcei(source[0], AL_BUFFER, buffer[0]);
	alSourcefv(source[0], AL_POSITION, srcPos);

	float lstPos[] = {0.0, 0.0, 0.0};
	alListenerfv(AL_POSITION, lstPos);

	alSourcePlay(source[0]);
	
	sleep(5);
	
	// Clear the things
	alDeleteSources(1, source);
	alDeleteBuffers(1, buffer);
	
	return 0;
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
#ifdef _WITH_OPENAL_
	Audio::Open();
//	sine_wave();
#endif

	InitWindow(854, 480); // TODO: read prefs.
	/*
	 * Shader support is required as I would like this to be fairly modern.
	 * As my laptop doesn't support OpenGL 3.x and far more hardware is around
	 * which supports 2.x anyways, 2.x will be the base.
	 *
	 * Most hardware which supports it should have enough power to handle this app.
	 * (Excluding some bottom end cards - I don't have high hopes for, say, a GF 6150)
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
#ifdef _WITH_OPENAL_
	Audio::Close();
#endif
	Log::Close();
	return 0;
}
