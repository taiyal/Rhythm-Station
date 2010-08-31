#include "Screen.h"
#include "Primitives.h"
#include "GameLoop.h"

Screen::Screen()
{
	Log::DebugPrint("[Screen::Screen] Creating screen.");
	img = new PNGLoader();
	img->Load("Themes/rstation-logo.png");

	std::string vs, fs;
	vs = "void main() {\
		gl_TexCoord[0]  = gl_MultiTexCoord0;\
		gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;\
	}";
	fs = "uniform sampler2D tex;\
	uniform float overlay_alpha;\
	void main()\
	{\
		vec4 texture = texture2D(tex, gl_TexCoord[0].st);\
		gl_FragColor = texture + (texture * overlay_alpha);\
	}";

	shader = new Shader();
	shader->Load(vs,fs);
	alphaLoc = glGetUniformLocation(shader->GetProgram(),"overlay_alpha");
	shader->Unbind();
	glfwEnable(GLFW_KEY_REPEAT);
	timer.Touch();
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

float alpha = 1.f;
float fade_length = 2.f;
bool bFinished = false;

void Screen::Update(float deltaTime)
{
	for(unsigned i = 0; i<vpActors.size(); i++)
		vpActors[i]->Update(deltaTime);

	float time = timer.Ago();
	if ( time <= fade_length )
	{
		alpha = interpolate(TWEEN_LINEAR, 1.0f, 0.0f, fade_length, time);
	}
	else if ( !bFinished )
	{
		bFinished = true;
		Log::Print("Finished tweening.");
		alpha = 0;
	}
}

void Screen::Draw()
{
	for(unsigned i = 0; i<vpActors.size(); i++)
		vpActors[i]->Draw();

	img->Bind();
	shader->Bind();
	glUniform1f(alphaLoc, alpha);
	Primitive::Quad(vec2(img->GetWidth(), img->GetHeight()));
}
