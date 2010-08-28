#include "Screen.h"
#include "Primitives.h"

Screen::Screen()
{
	Log::DebugPrint("[Screen::Screen] Creating screen.");
}

Screen::~Screen()
{
	Log::DebugPrint("[Screen::~Screen] Deleting.");
}

void Screen::Input(const IEvent &e)
{

}

void Screen::Update(float deltaTime)
{
	for(unsigned i = 0; i<vpActors.size(); i++)
		vpActors[i]->Update(deltaTime);
}

void Screen::Draw()
{
	for(unsigned i = 0; i<vpActors.size(); i++)
		vpActors[i]->Draw();
	
	Primitive::Quad(vec2(50,50));
}
