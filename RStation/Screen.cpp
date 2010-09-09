#include "Screen.h"
#include "Primitives.h"
#include "GameLoop.h"

Screen::Screen()
{
//	alphaLoc = glGetUniformLocation(shader->getProgram(),"overlay_alpha");
//	glfwEnable(GLFW_KEY_REPEAT);
//	timer.Touch();
}

Screen::~Screen() { }

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
	// when hitting a key you tend to get x being a huge negative number. weird.
	if(e.Mouse.moving && e.Mouse.x >= -1000.f)
	{
		// XXX: wtf.
		if(!vpActorHooks.empty())
			vpActorHooks.back()->Position(vec3(e.Mouse.x,e.Mouse.y,0));
	}
	if(e.Key == KEY_ESC )
		Game::Terminate();
}

//float alpha = 1.f;
//float fade_length = 2.f;
//bool bFinished = false;

void Screen::Update(float deltaTime)
{
	for(unsigned i = 0; i<vpActors.size(); i++)
		vpActors[i]->Update(deltaTime);

//	float time = timer.Ago();
//	if ( time <= fade_length )
//		alpha = interpolate(TWEEN_LINEAR, 1.0f, 0.0f, fade_length, time);
//	else if ( !bFinished )
//	{
//		bFinished = true;
//		Log::Print("Finished tweening.");
//		alpha = 0.f;
//	}
}

//int frame = 1;
void Screen::Draw()
{
	for(unsigned i = 0; i<vpActors.size(); i++)
		vpActors[i]->DrawBase();
	
/*	glPushMatrix();
		// XXX: the Gran Turismo trick; it only works for moving stuff.
		if ( ++frame % 2 )
			glTranslatef(0.5, 1, 0);
		else
			glTranslatef(0, 0, 0);
		*
		img->Bind();
		shader->Bind();
		glUniform1f(alphaLoc, alpha);
		Primitive::Quad(vec2(img->getWidth(), img->getHeight()));
	glPopMatrix();*/
}
