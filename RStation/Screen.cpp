#include "Screen.h"
#include "Primitives.h"

Screen::Screen()
{
	Log::DebugPrint("[Screen::Screen] Creating screen.");
	img = new PNGLoader();
	img->Load("image-png.png");
	
	std::string vs, fs;
	vs = "void main() { gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex; }";
	fs = "void main() { gl_FragColor = vec4(0.4,0.4,0.8,1.0); }";
	
	shader = new Shader();
	shader->Load(vs,fs);
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

	shader->Bind();
	glBindTexture(GL_TEXTURE_2D, img->GetTexture());
	Primitive::Quad(vec2(img->GetWidth(), img->GetHeight()));
	shader->Unbind();
//	Primitive::Ngon(40, 32);
}
