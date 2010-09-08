#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "RStation.h"
#include "InputManager.h"
#include "Actor.h"

class Screen
{
public:
	Screen();
	virtual ~Screen();

	void AddActor(Actor* actor);
	void AddHook(Actor* actor, ActorAttach attach);
	
	virtual void Input(const IEvent &e);
	virtual void Update(float deltaTime);
	virtual void Draw();
private:
	std::vector<Actor*> vpActors;
	std::vector<Actor*> vpActorHooks;

//	GLuint alphaLoc;
};

#endif