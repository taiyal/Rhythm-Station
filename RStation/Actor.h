#ifndef _ACTOR_H_
#define _ACTOR_H_

#include "RStation.h"
#include "MessageManager.h"

enum ActorAttach {
	RS_ATTACH_CURSOR
};

class Actor : public MessageSubscriber
{
public:
	Actor();
	virtual ~Actor() {}
	virtual void Update(float fDeltaTime) {}
	virtual void Draw() {}
	virtual void DrawBase();
	void AddChild(Actor* _child);
	void Hook(ActorAttach _attach);
	void Register();
	
	virtual void Position(vec3 _pos) { ob_pos = _pos; }
	virtual void Rotate(vec3 _rot) { ob_rot = _rot; }
	virtual void Scale(vec3 _scale) { ob_scale = _scale; }

	virtual vec3 getPosition() { return ob_pos; }
	virtual vec3 getRotate() { return ob_rot; }
	virtual vec3 getScale() { return ob_scale; }

protected:
	vec3 ob_pos;
	vec3 ob_rot;
	vec3 ob_scale;

	bool isHooked;

	Actor *parent;
	std::vector<Actor*> vpChildren;
};

#endif
