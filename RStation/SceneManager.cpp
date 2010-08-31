#include "RStation.h"
#include "Screen.h"
#include "SceneManager.h"
#include <GL/glfw.h>
#include "Sprite.h"

std::vector<Screen*> vpScreens;

void Scene::PushScreen()
{
	Screen* scr = new Screen();
	vpScreens.push_back(scr);
	Log::Print("[Scene::PushScreen] Pushed a new screen to the stack.");
	
	int spacing = 100;
	int num = 10;
	for (int i = -num; i<num; i++) {
		Sprite* spr = new Sprite();
		spr->Load("Themes/rstation-logo.png");
		spr->Position(vec3(i*spacing,100,0));
		spr->Rotate(vec3(0,0,45));
		spr->Scale(vec3(0.5));
		scr->AddActor(spr);
	}
}

void Scene::PopScreen()
{
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
	vpScreens.back()->Input(e);
}

void Scene::Clear()
{
	while(vpScreens.size())
	{
		delete vpScreens.back();
		vpScreens.pop_back();
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
