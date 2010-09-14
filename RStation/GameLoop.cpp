#include "RStation.h"
#include <GL/glfw.h>
#include "GameLoop.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "RSUtil.h"
#include "Screen.h"
#include "Sprite.h"
#include "Sound.h"

bool bRunning = true;

const int freq = 2; // update x times per second

namespace Game
{
	void Terminate()
	{
		bRunning = false;
	}
	void Run()
	{
		Timer timer;
		Scene::PushScreen(); // push overlay
		{
			Sprite *spr = new Sprite();
			spr->Load("Themes/rstation-logo.png");
			spr->Glow(rgba(0.125f, 0.125f, 0.125f, 0.0f));
			spr->Register();

			Sprite *spr_mouse = new Sprite();
			spr_mouse->Load("Themes/_arrow.png");
			spr_mouse->Hook(RS_ATTACH_CURSOR);
			int w = spr_mouse->getWidth();
			int h = spr_mouse->getHeight();
			spr_mouse->Offset(vec3(w/13.f,h/7.f,0)); // not perfect.
			spr_mouse->Rotate(vec3(0.f,0.f,-27.f));
			spr_mouse->Scale(vec3(0.35f,0.5f,1.f));
			spr_mouse->Register();

			Sound *sound = new Sound();
			sound->Load("Themes/shield-9.ogg");
			sound->Loop(true);
			sound->Register();
		}
		
		Log::Print("Loading took: " + timer.strAgo() + " seconds.");
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

			// update this first so we're on the right frame
			Input::Update();

			Scene::Update(delta);
			Scene::Draw();
		}
		Scene::Clear();
	}
}
