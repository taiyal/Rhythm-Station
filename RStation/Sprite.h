#ifndef _ACTOR_SPRITE_H_
#define _ACTOR_SPRITE_H_

#include "RStation.h"
#include "Actor.h"
#include "Tween.h"
#include "Timer.h"
#include "ShaderLoader.h"
#include "ImageLoader.h"

class Sprite : public Actor
{
public:
	Sprite();
	virtual ~Sprite();
	void Load(std::string _path);
	void SetFrames(vec2 frames);

	void Color(rgba _col);
	void Glow(rgba _col);
	void Hue(float _hue) { ob_hueShift = _hue; }
	void Saturation(float _sat) { ob_satShift = _sat; }
	rgba getColor();
	rgba getGlow();
	float getHue() { return ob_hueShift; }
	float getSaturation() { return ob_satShift; }

	int getWidth();
	int getHeight();
	int getUnscaledWidth();
	int getUnscaledHeight();

	void Update(float deltaTime);
	void Draw();

protected:
	float ob_hueShift, ob_satShift;
	rgba ob_color, ob_glow;

	ImageLoader* ob_texture;
	ShaderLoader* ob_shader;
	
	GLuint ob_buffer, ob_pColor, ob_pGlow, ob_pHueShift, ob_pSatShift;
};

#endif
