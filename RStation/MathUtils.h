#ifndef _Math_Utils_H_
#define _Math_Utils_H_

#include "RStation.h"

// PI is constant, obviously.
#define PI			3.1415926535897932384626433832795f
#define PI2			PI*PI
#define PHI			1.618f
#define GRAVITY	9.80665f

// a bunch of useful macros
// uncomment when needed.
#define SCALE(x, l1, h1, l2, h2)	(((x) - (l1)) * ((h2) - (l2)) / ((h1) - (l1)) + (l2))
#define CLAMP(a,b,c)			(a < b ? b : (a > c ? c : a))
#define WRAP(x,y)				((unsigned)x % y)
#define ABS(x)				(((x) < 0 ? (-x) : (x)))

#define sign(x)				(((x) > 0) ? 1 : ((x) < 0) ? -1 : 0)
#define smallest(x,y)			(ABS(x) < ABS(y) ? 0 : x)
#ifndef min
#define min(x,y)				((x) < (y) ? x : y)
#endif
#ifndef max
#define max(x,y)				((x) > (y) ? x : y)
#endif
//#define swap(a,b)				{ int temp = a; a = b; b = temp; }

float radf(float val);
float degf(float val);

#endif
