#include "RStation.h"
#include <GL/glfw.h>
#include "GameLoop.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "RSUtil.h"
#include "Screen.h"

bool bRunning = true;

// this will need to be declared in SceneManager probably.
InputManager* Input = new InputManager();

const int freq = 2; // update x times per second

namespace Game
{
	void Terminate()
	{
		bRunning = false;
	}
	void Run()
	{
		Scene::PushScreen(); // push initial screen

		// Init is done, flush the log.
		Log::Write();

		double then = glfwGetTime();
		while(bRunning && glfwGetWindowParam(GLFW_OPENED))
		{
			// calculate delta time
			double now = glfwGetTime();
			float delta = float(now - then);

			// calculate FPS and set window title.
			if( int(then * freq) != int(now * freq) )
				Util::UpdateWindowTitle(delta);

			then = now;

			Scene::Update(delta);
			Input->Update(); // singleton for some reason

			// Draw!
			Scene::Draw();
		}

		Scene::Clear();
	}
}
