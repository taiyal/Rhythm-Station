#include "RStation.h"
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
	int spacing = 100;
	int num = 5;
	for (int i = -num; i<num; i++) {
		Sprite* spr = new Sprite();
		spr->Load("Themes/rstation-logo.png");
		spr->Position(vec3(float((i+0.5)*spacing),100.0f,0.0f));
		spr->Rotate(vec3(0,0,45));
		spr->Scale(vec3(0.5));
		scr->AddActor(spr);
	}
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

void Scene::Update(float deltaTime)
{
	for(unsigned i = 0; i<vpScreens.size(); i++)
		vpScreens[i]->Update(deltaTime);
}

void Scene::SendInput(const IEvent &e)
{
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

	// recursively draw everything
	for(unsigned i = 0; i<vpScreens.size(); i++)
		vpScreens[i]->Draw();

	glfwSwapBuffers();
}
