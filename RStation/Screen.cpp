#include "Screen.h"
#include "Primitives.h"

Screen::Screen()
{
	Log::DebugPrint("[Screen::Screen] Creating screen.");
	img = new PNGLoader();
	img->Load("image-png.png");
	
	std::string vs, fs;
	vs =
	"void main()\n\
	{\n\
		gl_Position = ftransform(); // deprecated\n\
	}\n";
	
	fs =
	"void main() {\n\
	{\n\
		gl_FragColor = vec4(1.0);\n\
	}\n";
	
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
