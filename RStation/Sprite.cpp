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
	
	ob_shader->Load("sprite.vert","sprite.frag");
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
	ob_shader->Unbind();
	ob_texture->Unbind();
}
