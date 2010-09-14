#include "Actor.h"
#include "Screen.h"
#include "SceneManager.h"

Actor::Actor() :
	ob_pos(vec3(0.0f)),
	ob_rot(vec3(0.0f)),
	ob_scale(vec3(1.0f)),
	ob_offset(vec3(0.0f)),
	isHooked(false),
	ob_visible(true)
{ /* only used to initialize variables */ }

void Actor::AddChild(Actor *child)
{
	child->parent = this;
	vpChildren.push_back(child);
}

void Actor::Register()
{
	Screen* scr = Scene::GetTopScreen();
	scr->AddActor(this);
}

void Actor::Hook(ActorAttach _attach)
{
	Screen* scr = Scene::GetTopScreen();
	scr->AddHook(this, _attach);
	isHooked = true;
}

// Do the transforms and stuff which are going to be the same for nearly everything.
void Actor::DrawBase()
{
	// don't draw this or its children if invisible.
	if(!ob_visible)
		return;
	// XXX: clear the z-buffer if hooked. This should be its own setting.
	if(isHooked) { glClear(GL_DEPTH_BUFFER_BIT); }
	glPushMatrix();
		glTranslatef(ob_pos.x+ob_offset.x, ob_pos.y+ob_offset.y, ob_pos.z+ob_offset.z);
		glPushMatrix();
			glRotatef(ob_rot.x, 1, 0, 0);
			glRotatef(ob_rot.y, 0, 1, 0);
			glRotatef(ob_rot.z, 0, 0, 1);
			glPushMatrix();
				glScalef(ob_scale.x, ob_scale.y, ob_scale.z);
				// draw recursively.
				this->Draw();
				for (unsigned i = 0; i<vpChildren.size(); i++)
					vpChildren[i]->DrawBase();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}
