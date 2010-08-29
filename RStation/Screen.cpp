#include "Screen.h"
#include "Primitives.h"

Screen::Screen()
{
	Log::DebugPrint("[Screen::Screen] Creating screen.");
	img = new PNGLoader();
	img->Load("image-png.png");
}

Screen::~Screen()
{
	Log::DebugPrint("[Screen::~Screen] Deleting.");
	img->Unload();
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

	glBindTexture(GL_TEXTURE_2D, img->GetTexture());
	Primitive::Quad(vec2(img->GetWidth(),img->GetHeight()));
//	Primitive::Ngon(40, 32);
}
