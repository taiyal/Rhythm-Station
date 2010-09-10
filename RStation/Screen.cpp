#include "Screen.h"
#include "Primitives.h"
#include "GameLoop.h"

Screen::Screen()
{
//	alphaLoc = glGetUniformLocation(shader->getProgram(),"overlay_alpha");

	// don't want to mix with other screens, if this comes later it's on top.
	glClear(GL_DEPTH_BUFFER_BIT);
}

Screen::~Screen()
{
	while(!vpActors.empty())
	{
		delete vpActors.back();
		vpActors.pop_back();
	}
}

void Screen::AddActor(Actor* _actor)
{
	vpActors.push_back(_actor);
}

void Screen::AddHook(Actor* _actor, ActorAttach _attach)
{
	if(_attach == RS_ATTACH_CURSOR)
		vpActorHooks.push_back(_actor);
}

void Screen::Input(const IEvent &e)
{
	// XXX: ???
	if(e.Mouse.moving)
		if(!vpActorHooks.empty())
			vpActorHooks.back()->Position(vec3(e.Mouse.x,e.Mouse.y,0));
	
	if(e.Key == KEY_ESC )
		Game::Terminate();
}

void Screen::Update(float deltaTime)
{
	for(unsigned i = 0; i<vpActors.size(); i++)
		vpActors[i]->Update(deltaTime);
}

void Screen::Draw()
{
	for(unsigned i = 0; i<vpActors.size(); i++)
		vpActors[i]->DrawBase();
//	glUniform1f(alphaLoc, alpha);
}
