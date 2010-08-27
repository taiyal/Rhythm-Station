#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "RStation.h"
#include "InputManager.h"

namespace Scene
{
	void PushScreen();
	void PopScreen();
	
	void SendInput(const IEvent &e);
	void Update(float deltaTime);
	void Draw();
	
	void Clear();
};

#endif
