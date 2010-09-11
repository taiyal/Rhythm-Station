#include "RStation.h"
#include "MathUtils.h"
#include "Screen.h"
#include "SceneManager.h"
#include <GL/glfw.h>
#include "Sprite.h"
#include "Timer.h"

std::vector<Screen*> vpScreens;

void Scene::PushScreen()
{
	Screen* scr = new Screen();
	vpScreens.push_back(scr);
	Log::Print("[Scene::PushScreen] Pushed a new screen to the stack.");
	
	Timer timer;
	Sprite* spr = new Sprite();
	spr->Load("Themes/rstation-logo.png");
	spr->Rotate(vec3(0,0,0));
	spr->Register();
	
	Log::Print("[Scene::PushScreen] Loading took: " + timer.strAgo() + " seconds.");
}

void Scene::PopScreen()
{
	if(vpScreens.empty())
	{
		Log::Print("No Screens to delete!");
		return;
	}
	delete vpScreens.back();
	vpScreens.pop_back();

	Log::Print("[Scene::PopScreen] Deleted top screen.");
}

Screen* Scene::GetTopScreen()
{
	return vpScreens.back();
}

void Scene::Update(float deltaTime)
{
	for(unsigned i = 0; i<vpScreens.size(); i++)
		vpScreens[i]->Update(deltaTime);
}

void Scene::SendInput(IEvent &e)
{
	// this happens if mouse wasn't set by the sender.
	if(e.Mouse.x < -200000)
		e.Mouse = MouseInfo();

	if(!vpScreens.empty())
		vpScreens.back()->Input(e);
}

void Scene::Clear()
{
	while(!vpScreens.empty())
	{
		PopScreen();
	}
	Log::Print("[Scene::Clear] Cleared all screens.");
}

void Scene::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// draw all screens and their children
	for(unsigned i = 0; i<vpScreens.size(); i++)
		vpScreens[i]->Draw();

	glfwSwapBuffers();
}
