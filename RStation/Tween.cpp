#include "Tween.h"
#include <math.h>

typedef float (*TweenFn) (float,float,float);

float sleep( float change, float time, float elapsed )
{
	if ( elapsed == 1 )
		return change;
	return 0.0f;
}

float linear( float change, float time, float elapsed )
{
	return change * elapsed;
}

float ease_in( float change, float time, float elapsed )
{
	return change * elapsed * time;
}

float ease_out( float change, float time, float elapsed )
{
	return change * ((1-elapsed)+1) * time;
}

float smooth( float change, float time, float elapsed )
{
	// this might be wrong?
	if ((elapsed/2) < 1)
		return change * powf(elapsed, 2);
	return change * (powf(elapsed-2, 2) + 2);
}

float ease_in_cubic( float change, float time, float elapsed )
{
	return change * powf(elapsed, 3);
}

float ease_out_cubic( float change, float time, float elapsed )
{
	return change * (powf(elapsed-1, 3)+1);
}

float smooth_cubic( float change, float time, float elapsed )
{
	if ((elapsed/2) < 1)
		return change * powf(elapsed, 3);
	return change * (powf(elapsed-1, 3) + 1);
}

TweenFn SetTweenType( int type )
{
	TweenFn Tween = NULL;
	switch ( type )
	{
		case TWEEN_SLEEP:
			Tween = &sleep;
			break;
		case TWEEN_LINEAR:
			Tween = &linear;
			break;
		case TWEEN_EASE_IN: // 2
			Tween = &ease_in;
			break;
		case TWEEN_EASE_OUT: // 3
			Tween = &ease_out;
			break;
		case TWEEN_SMOOTH: // 4
			Tween = &smooth;
			break;
		case TWEEN_EASE_IN_CUBIC: // 5
			Tween = &ease_in_cubic;
			break;
		case TWEEN_EASE_OUT_CUBIC: // 6
			Tween = &ease_out_cubic;
			break;
		case TWEEN_SMOOTH_CUBIC: // 7
			Tween = &smooth_cubic;
			break;
		default:
			Tween = &linear;
			break;
	}
	return Tween;
}

float interpolate( int tweentype, float _old, float _new, float duration, float time )
{
	if ( duration == 0 )
		return _new; // don't divide by zero and don't bother with doing any math.

	float temp = _old;
	float elapsed = time / duration;
	float change = _old - _new; // old - new = difference.
	
	TweenFn Tween = SetTweenType(tweentype);
	
	if( Tween )
	{
		temp -= Tween( change, time, elapsed );
	}
	return temp;
}

/*
 * Overloads for vec2, vec3 and rgba.
 * This is messy, but it's hard to do any better here. I may end up just phasing out these
 * completely and just call interpolate (float) more times in the code that needs this.
 */
vec2 interpolate( int tweentype, vec2 _old, vec2 _new, float duration, float time )
{
	if ( duration == 0 )
		return _new;

	vec2 temp = _old;
	float elapsed = time / duration;
	
	// note: vec2 etc need some operators
	vec2 change;
	change.x = _old.x - _new.x;
	change.y = _old.y - _new.y;
	
	TweenFn Tween = SetTweenType(tweentype);
	
	if( Tween )
	{
		temp.x -= Tween( change.x, time, elapsed );
		temp.y -= Tween( change.y, time, elapsed );
	}
	return temp;
}

vec3 interpolate( int tweentype, vec3 _old, vec3 _new, float duration, float time )
{
	if ( duration == 0 )
		return _new;

	vec3 temp = _old;
	float elapsed = time / duration;
	
	vec3 change;
	change.x = _old.x - _new.x;
	change.y = _old.y - _new.y;
	change.z = _old.z - _new.z;
	
	TweenFn Tween = SetTweenType(tweentype);
	
	if( Tween )
	{
		temp.x -= Tween( change.x, time, elapsed );
		temp.y -= Tween( change.y, time, elapsed );
		temp.z -= Tween( change.z, time, elapsed );
	}
	return temp;
}

rgba interpolate( int tweentype, rgba _old, rgba _new, float duration, float time )
{
	if ( duration == 0 )
		return _new;

	rgba temp = _old;
	float elapsed = time / duration;
	
	rgba change;
	change.r = _old.r - _new.r;
	change.g = _old.g - _new.g;
	change.b = _old.b - _new.b;
	change.a = _old.a - _new.a;
	
	TweenFn Tween = SetTweenType(tweentype);
	
	if( Tween )
	{
		temp.r -= Tween( change.r, time, elapsed );
		temp.g -= Tween( change.g, time, elapsed );
		temp.b -= Tween( change.b, time, elapsed );
		temp.a -= Tween( change.a, time, elapsed );
	}
	return temp;
}
