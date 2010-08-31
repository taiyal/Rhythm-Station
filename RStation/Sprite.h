#ifndef _ACTOR_SPRITE_H_
#define _ACTOR_SPRITE_H_

#include "RStation.h"
#include "Actor.h"
#include "Tween.h"
#include "Timer.h"
#include "Shader.h"
#include "ImageLoader.h"

class Sprite : public Actor
{
public:
	Sprite();
	virtual ~Sprite();
	void Load(std::string _path);
	void SetFrames(vec2 frames);

	void Color(rgba _col);
	void ColorAdd(rgba _col);
	rgba getColor();

	void Update(float deltaTime);
	void Draw();

protected:
	rgba ob_color;

	ImageLoader* ob_texture;
	Shader* ob_shader;
	
	GLuint ob_buffer;
};

#endif
