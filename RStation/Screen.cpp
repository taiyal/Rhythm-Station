#include "Screen.h"
#include "Primitives.h"
#include "GameLoop.h"
#include "Timer.h"
#include "Tween.h"

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
	glfwEnable(GLFW_KEY_REPEAT);
}

Screen::~Screen()
{
	Log::DebugPrint("[Screen::~Screen] Deleting.");
	img->Unload();
}

vec3 pos = vec3(5,5,0);
vec3 dest, temp = pos;

Timer timer;

bool bMoving = false;

void Move(float x, float y)
{
	if ( bMoving )
		return;
	bMoving = true;
	dest.x += x;
	dest.y += y;
	timer.Touch();
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
	if ( e.Key == KEY_LEFT )
		Move(-5,0);
	if ( e.Key == KEY_RIGHT )
		Move(5,0);
	if ( e.Key == KEY_UP )
		Move(0,-5);
	if ( e.Key == KEY_DOWN )
		Move(0,5);
}

void Screen::Update(float deltaTime)
{
	for(unsigned i = 0; i<vpActors.size(); i++)
		vpActors[i]->Update(deltaTime);
	
	float time = timer.Ago();
	if ( bMoving )
	{
		if ( time >= 0.25f )
		{
			bMoving = false;
			pos = dest;
			return;
		}
		else
		{
			temp = interpolate( TWEEN_LINEAR, pos, dest, 0.25f, time );
		}

	}
}

void Screen::Draw()
{
	for(unsigned i = 0; i<vpActors.size(); i++)
		vpActors[i]->Draw();

	shader->Bind();
	img->Bind();
	
	Primitive::Quad(vec2(img->GetWidth(), img->GetHeight()));
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	shader->Unbind();
	
	glPushMatrix();
	glTranslatef(temp.x, temp.y, 0);
	Primitive::Quad(vec2(img->GetWidth(), img->GetHeight()));
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPopMatrix();
}
