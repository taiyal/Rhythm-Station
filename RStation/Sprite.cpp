#include "Sprite.h"
#include "PNGLoader.h"
#include "Primitives.h"

Sprite::Sprite() : ob_color(rgba(1.f)), ob_glow(rgba(0.f, 0.f))
{
	ob_texture = new ImageLoader(); // make sure this exists!
	ob_shader = new ShaderLoader();
}

Sprite::~Sprite()
{
	delete ob_texture;
	delete ob_shader;
}

// various commands - easy stuff.
void Sprite::Color(rgba _col) { ob_color = _col; }
void Sprite::Glow(rgba _col) { ob_glow = _col; }

rgba Sprite::getColor() { return ob_color; }
rgba Sprite::getGlow() { return ob_glow; }

int Sprite::getWidth() { return ob_texture->getWidth() * ob_scale.x; }
int Sprite::getHeight() { return ob_texture->getHeight() * ob_scale.y; }
int Sprite::getUnscaledWidth() { return ob_texture->getWidth(); }
int Sprite::getUnscaledHeight() { return ob_texture->getHeight(); }

// the business end of things
void Sprite::Load(std::string _path)
{
	delete ob_texture;
	ob_texture = new PNGLoader();
	ob_texture->Load(_path);
	ob_shader->Load("sprite.vert","sprite.frag");
	ob_pColor = glGetUniformLocation(ob_shader->getProgram(), "color");
	ob_pGlow = glGetUniformLocation(ob_shader->getProgram(), "glow");
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
	glUniform4f(ob_pGlow, ob_glow.r, ob_glow.g, ob_glow.b, ob_glow.a);
	glUniform4f(ob_pColor, ob_color.r, ob_color.g, ob_color.b, ob_color.a);

	Primitive::Quad(vec2(ob_texture->getWidth(), ob_texture->getHeight()));
	ob_shader->Unbind();
	ob_texture->Unbind();
}
