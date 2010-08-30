#include "Screen.h"
#include "Primitives.h"
#include "GameLoop.h"

Screen::Screen()
{
	Log::DebugPrint("[Screen::Screen] Creating screen.");
	img = new PNGLoader();
	img->Load("image-png.png");
	
	std::string vs, fs;
	vs = "void main() {\
		gl_TexCoord[0]  = gl_MultiTexCoord0;\
		gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;\
	}";
	fs = "uniform sampler2D tex;\
	void main()\
	{\
		vec4 texture = texture2D(tex, gl_TexCoord[0].st);\
		gl_FragColor = texture * vec4(0.4,0.4,0.8,1.0);\
	}";
	
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
	Log::Print("Input recieved.");
	if ( e.Key == KEY_F1 && e.State == RS_FIRST_PRESS )
	{
		Log::Print("Unloading");
		shader->Unbind();
		shader->Unload();
	}
	if ( e.Key == KEY_ESC )
	{
		Game::Terminate();
	}
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
	img->Bind();
	
	Primitive::Quad(vec2(img->GetWidth(), img->GetHeight()));
}
