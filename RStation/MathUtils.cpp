#include "MathUtils.h"

float radf(float val)
{
	// cast as float so the conversion is explicit.
	val = float(val * .017453292f); // PI / 180.f (precalculated)
	return val;
}

float degf(float val)
{
	val = float(val * 57.29577951f); // 180.f / PI (precalculated)
	return val;
}
