#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "RStation.h"
#include "InputManager.h"
#include "Actor.h"
#include "PNGLoader.h"

class Screen
{
public:
	Screen();
	virtual ~Screen();

	virtual void Input(const IEvent &e);
	virtual void Update(float deltaTime);
	virtual void Draw();
private:
	std::vector<Actor*> vpActors;
	PNGLoader* img;
};

#endif