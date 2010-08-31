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
	void main()\
	{\
		vec4 texture = texture2D(tex, gl_TexCoord[0].st);\
		gl_FragColor = texture * vec4(0.4,0.4,0.8,1.0);\
	}";
	
	shader = new Shader();
	shader->Load(vs,fs);
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

float alpha = 0.f;
float fade_length = 1.5f;

void Screen::Update(float deltaTime)
{
	for(unsigned i = 0; i<vpActors.size(); i++)
		vpActors[i]->Update(deltaTime);
	
	float time = timer.Ago();
	if ( time <= fade_length )
		alpha = interpolate(TWEEN_EASE_OUT, 1.0f, 0.0f, fade_length, time);
}

void Screen::Draw()
{
	for(unsigned i = 0; i<vpActors.size(); i++)
		vpActors[i]->Draw();
	
	glPushMatrix();
		img->Bind();
		//shader->Bind();
		Primitive::Quad(vec2(img->GetWidth(), img->GetHeight()));	
		//shader->Unbind();
		
		// additive blend and alpha fade
		glColor4f(1.f, 1.f, 1.f, alpha);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		Primitive::Quad(vec2(img->GetWidth(), img->GetHeight()));
		
		// reset color and blend
		glColor4f(1.f, 1.f, 1.f, 1.f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // normal blend
	glPopMatrix();
}
