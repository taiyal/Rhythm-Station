#include "Tween.h"
#include <math.h>

/*
vyhd help:
ypedef float (*TweenFn)(float,float,float);
(...)
TweenFn Tween = NULL;
switch( tweentype )
{
    case TWEEN_LINEAR:    Tween = &tweens::linear; break;
    case TWEEN_EASE_IN: Tween = &tweens::easeIn; break;
(...)
}
    if( Tween )
    {
        temp.x -= Tween( change.x, time, elapsed );
        temp.y -= Tween( change.y, time, elapsed );
        temp.z -= Tween( change.z, time, elapsed );
    }
*/

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
		temp -=tweens::linear( change, elapsed );
		break;
	}
	return temp;
}
