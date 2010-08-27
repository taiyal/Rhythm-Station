#ifndef _Tween_H_
#define _Tween_H_
#include "Type.h"

enum TweenTypes
{
	TWEEN_SLEEP,
	TWEEN_LINEAR,
	TWEEN_EASE_IN, // this and the next are a little disfunctional.
	TWEEN_EASE_OUT,
	TWEEN_SMOOTH,
	TWEEN_EASE_IN_CUBIC,
	TWEEN_EASE_OUT_CUBIC,
	TWEEN_SMOOTH_CUBIC
};

namespace tweens
{
	float linear( float change, float elapsed );
	float easeIn( float change, float time, float elapsed );
	float easeOut( float change, float time, float elapsed );
	float easeSmooth( float change, float time, float elapsed );
	float easeInCubic( float change, float time, float elapsed );
	float easeOutCubic( float change, float time, float elapsed );
	float easeSmoothCubic( float change, float time, float elapsed );
}

float interpolate( int tweentype, float _old, float _new, float duration, float time );
vec3 interpolate( int tweentype, vec3 _old, vec3 _new, float duration, float time );
rgba interpolate( int tweentype, rgba _old, rgba _new, float duration, float time );

#endif
