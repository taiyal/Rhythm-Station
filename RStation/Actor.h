#ifndef _ACTOR_H_
#define _ACTOR_H_

#include "MessageManager.h"

class Actor : public MessageSubscriber {
public:
	virtual void Update(float fDeltaTime) {}
	virtual void Draw() {}
};

#endif
