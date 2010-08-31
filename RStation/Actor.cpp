#include "Actor.h"

//void Actor::Update(float deltaTime) { }
//void Actor::Draw() { }

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
				// draw self
				this->Draw();
				// TODO: draw children
//				for (unsigned i = 0; i<vpChildren.size(); i++) { vpChildren[i]->DrawBase(); }
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}