#include "Actor.h"
#include "Screen.h"
#include "SceneManager.h"

Actor::Actor()
{
	ob_scale = vec3(1.0f);
}

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
}

// Do the transforms and stuff which are going to be the same for nearly everything.
void Actor::DrawBase()
{
	glPushMatrix();
		glTranslatef(ob_pos.x, ob_pos.y, ob_pos.z);
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
