#include "Sprite.h"
#include "PNGLoader.h"
#include "Primitives.h"

Sprite::Sprite()
{
	ob_texture = new ImageLoader(); // make sure this exists!
	ob_shader = new Shader();
}
Sprite::~Sprite()
{
	delete ob_texture;
	delete ob_shader;
}

// various commands - easy stuff.
void Sprite::Color(rgba _col) { ob_color = _col; }

rgba Sprite::getColor() { return ob_color; }

// the business end of things
void Sprite::Load(std::string _path)
{
	delete ob_texture;
	ob_texture = new PNGLoader();
	ob_texture->Load(_path);
	
	std::string vs, fs;
	vs = "void main() {\
		gl_TexCoord[0]  = gl_MultiTexCoord0;\
		gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;\
	}";
	fs = "uniform sampler2D tex;\
	void main()\
	{\
		vec4 texture = texture2D(tex, gl_TexCoord[0].st);\
		gl_FragColor = texture;\
	}";
	
	ob_shader->Load(vs,fs);
}
void Sprite::SetFrames(vec2 frames)
{
	// TODO
}

//void Sprite::AddCommand(int type, float length);

void Sprite::Update(float deltaTime) { }

void Sprite::Draw()
{
	ob_texture->Bind();
	ob_shader->Bind();
	Primitive::Quad(vec2(ob_texture->getWidth(), ob_texture->getHeight()));
}
