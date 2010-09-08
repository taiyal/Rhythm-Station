#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "RStation.h"
#include "InputManager.h"
#include "Screen.h"

namespace Scene
{
	void PushScreen();
	void PopScreen();

	Screen* GetTopScreen();
	void SendInput(const IEvent &e);
	void Update(float deltaTime);
	void Draw();

	void Clear();
};

#endif
