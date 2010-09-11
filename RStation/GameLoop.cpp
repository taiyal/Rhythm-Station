#include "RStation.h"
#include <GL/glfw.h>
#include "GameLoop.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "RSUtil.h"
#include "Screen.h"
#include "Sprite.h"

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
		
		Scene::PushScreen(); // push overlay
		{
			Sprite* spr_mouse = new Sprite();
			spr_mouse->Load("Themes/_arrow.png");
			spr_mouse->Hook(RS_ATTACH_CURSOR);
			int w, h;
			w = spr_mouse->getWidth();
			h = spr_mouse->getHeight();
			spr_mouse->Offset(vec3(w/13.f,h/7.f,0)); // not perfect.
			spr_mouse->Rotate(vec3(0,0,-27));
			spr_mouse->Scale(vec3(0.35,0.5,1));
			spr_mouse->Register();
		}
		
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
