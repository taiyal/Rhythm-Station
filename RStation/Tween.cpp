#include "Tween.h"
#include <math.h>

float tweens::linear( float change, float elapsed )
{
	return change * elapsed;
}

float tweens::easeIn( float change, float time, float elapsed )
{
	return change * elapsed * time;
}

float tweens::easeOut( float change, float time, float elapsed )
{
	return change * ((1-elapsed)+1) * time;
}

float tweens::easeSmooth( float change, float time, float elapsed )
{
	// this might be wrong?
	if ((elapsed/2) < 1)
		return change * powf(elapsed, 2);
	return change * (powf(elapsed-2, 2) + 2);
}

float tweens::easeInCubic( float change, float time, float elapsed )
{
	return change * powf(elapsed, 3);
}

float tweens::easeOutCubic( float change, float time, float elapsed )
{
	return change * (powf(elapsed-1, 3)+1);
}

float tweens::easeSmoothCubic( float change, float time, float elapsed )
{
	if ((elapsed/2) < 1)
		return change * powf(elapsed, 3);
	return change * (powf(elapsed-1, 3) + 1);
}


// linear interpolation
float interpolate( int tweentype, float _old, float _new, float duration, float time )
{
	float temp = _old;
	if ( duration == 0 )
		return _new; // prevent a divide by zero and save some effort.
	
	float elapsed = time / duration;
	
	// get the difference between the old position and the new one. (old - new)
	float change = _old;
	change -= _new;
	
	// warning: big ugly switch
	switch ( tweentype )
	{
	case TWEEN_SLEEP: // 0
		if ( elapsed == 1 )
			temp = _new;
		break;
	case TWEEN_LINEAR: // 1
	linear:
		temp -= tweens::linear( change, elapsed );
		break;
	case TWEEN_EASE_IN: // 2
		temp -= tweens::easeIn( change, time, elapsed );
		break;
	case TWEEN_EASE_OUT: // 3
		temp -= tweens::easeOut( change, time, elapsed );
		break;
	case TWEEN_SMOOTH: // 4
		temp -= tweens::easeSmooth( change, time, elapsed );
		break;
	case TWEEN_EASE_IN_CUBIC: // 5
		temp -= tweens::easeInCubic( change, time, elapsed );
		break;
	case TWEEN_EASE_OUT_CUBIC: // 6
		temp -= tweens::easeOutCubic( change, time, elapsed );
		break;
	case TWEEN_SMOOTH_CUBIC: // 7
		temp -= tweens::easeSmoothCubic( change, time, elapsed );
		break;
	default:
		goto linear;
		break;
	}
	return temp;
}

vec3 interpolate( int tweentype, vec3 _old, vec3 _new, float duration, float time )
{
	vec3 temp = _old;
	if ( duration == 0 )
		return _new; // prevent a divide by zero and save some effort.
	
	float elapsed = time / duration;
	
	// get the difference between the old position and the new one. (old - new)
	vec3 change = _old;
	change.x -= _new.x;
	change.y -= _new.y;
	change.z -= _new.z;
	
	// warning: big ugly switch
	switch ( tweentype )
	{
	case TWEEN_SLEEP: // 0
		if ( elapsed == 1 )
			temp = _new;
		break;
	case TWEEN_LINEAR: // 1
	linear:
		temp.x -= tweens::linear( change.x, elapsed );
		temp.y -= tweens::linear( change.y, elapsed );
		temp.z -= tweens::linear( change.z, elapsed );
		break;
	case TWEEN_EASE_IN: // 2
		temp.x -= tweens::easeIn( change.x, time, elapsed );
		temp.y -= tweens::easeIn( change.y, time, elapsed );
		temp.z -= tweens::easeIn( change.z, time, elapsed );
		break;
	case TWEEN_EASE_OUT: // 3
		temp.x -= tweens::easeOut( change.x, time, elapsed );
		temp.y -= tweens::easeOut( change.y, time, elapsed );
		temp.z -= tweens::easeOut( change.z, time, elapsed );
		break;
	case TWEEN_SMOOTH: // 4
		temp.x -= tweens::easeSmooth( change.x, time, elapsed );
		temp.y -= tweens::easeSmooth( change.y, time, elapsed );
		temp.z -= tweens::easeSmooth( change.z, time, elapsed );
		break;
	case TWEEN_EASE_IN_CUBIC: // 5
		temp.x -= tweens::easeInCubic( change.x, time, elapsed );
		temp.y -= tweens::easeInCubic( change.y, time, elapsed );
		temp.z -= tweens::easeInCubic( change.z, time, elapsed );
		break;
	case TWEEN_EASE_OUT_CUBIC: // 6
		temp.x -= tweens::easeOutCubic( change.x, time, elapsed );
		temp.y -= tweens::easeOutCubic( change.y, time, elapsed );
		temp.z -= tweens::easeOutCubic( change.z, time, elapsed );
		break;
	case TWEEN_SMOOTH_CUBIC: // 7
		temp.x -= tweens::easeSmoothCubic( change.x, time, elapsed );
		temp.y -= tweens::easeSmoothCubic( change.y, time, elapsed );
		temp.z -= tweens::easeSmoothCubic( change.z, time, elapsed );
		break;
	default:
		goto linear;
		break;
	}
	return temp;
}

// XXX: duped for color this is really really bad.
// I am in fact ashamed of myself for duplicating this large of a block.
rgba interpolate( int tweentype, rgba _old, rgba _new, float duration, float time )
{
	rgba temp = _old;
	if ( duration == 0.f )
		return _new; // prevent a divide by zero and save some effort.

	float elapsed = time / duration;
	
	// get the difference between the old position and the new one. (old - new)
	rgba change = _old;
	change.r -= _new.r;
	change.g -= _new.g;
	change.b -= _new.b;
	change.a -= _new.a;
	
	// warning: big ugly switch
	switch ( tweentype )
	{
	case TWEEN_SLEEP: // 0
		if ( elapsed == 1 )
			temp = _new;
		break;
	case TWEEN_LINEAR: // 1
	linear_:
		temp.r -= tweens::linear( change.r, elapsed );
		temp.g -= tweens::linear( change.g, elapsed );
		temp.b -= tweens::linear( change.b, elapsed );
		temp.a -= tweens::linear( change.a, elapsed );
		break;
	case TWEEN_EASE_IN: // 2
		temp.r -= tweens::easeIn( change.r, time, elapsed );
		temp.g -= tweens::easeIn( change.g, time, elapsed );
		temp.b -= tweens::easeIn( change.b, time, elapsed );
		temp.a -= tweens::easeIn( change.a, time, elapsed );
		break;
	case TWEEN_EASE_OUT: // 3
		temp.r -= tweens::easeOut( change.r, time, elapsed );
		temp.g -= tweens::easeOut( change.g, time, elapsed );
		temp.b -= tweens::easeOut( change.b, time, elapsed );
		temp.a -= tweens::easeOut( change.a, time, elapsed );
		break;
	case TWEEN_SMOOTH: // 4
		temp.r -= tweens::easeSmooth( change.r, time, elapsed );
		temp.g -= tweens::easeSmooth( change.g, time, elapsed );
		temp.b -= tweens::easeSmooth( change.b, time, elapsed );
		temp.a -= tweens::easeSmooth( change.a, time, elapsed );
		break;
	case TWEEN_EASE_IN_CUBIC: // 5
		temp.r -= tweens::easeInCubic( change.r, time, elapsed );
		temp.g -= tweens::easeInCubic( change.g, time, elapsed );
		temp.b -= tweens::easeInCubic( change.b, time, elapsed );
		temp.a -= tweens::easeInCubic( change.a, time, elapsed );
		break;
	case TWEEN_EASE_OUT_CUBIC: // 6
		temp.r -= tweens::easeOutCubic( change.r, time, elapsed );
		temp.g -= tweens::easeOutCubic( change.g, time, elapsed );
		temp.b -= tweens::easeOutCubic( change.b, time, elapsed );
		temp.a -= tweens::easeOutCubic( change.a, time, elapsed );
		break;
	case TWEEN_SMOOTH_CUBIC: // 7
		temp.r -= tweens::easeSmoothCubic( change.r, time, elapsed );
		temp.g -= tweens::easeSmoothCubic( change.g, time, elapsed );
		temp.b -= tweens::easeSmoothCubic( change.b, time, elapsed );
		temp.a -= tweens::easeSmoothCubic( change.a, time, elapsed );
		break;
	default:
		// lol goto
		goto linear_;
		break;
	}
	return temp;
}
