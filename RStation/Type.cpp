#include "Type.h"

std::string convert::toString(int _in)
{
	std::stringstream out;
	out << _in;
	return out.str();
}
std::string convert::toString(double _in)
{
	std::stringstream out;
	out << _in;
	return out.str();
}
std::string convert::toString(bool _in)
{
	std::stringstream out;
	if ( _in )
		out << "true";
	else
		out << "false";
	return out.str();
}

// vec2
vec2::vec2() {
	x = y = 0.0f;
}
vec2::vec2(float _xy)
{
	x = y = _xy;
}
vec2::vec2(float _x, float _y)
{
	x = _x;
	y = _y;
}

// vec3
vec3::vec3() {
	x = y = z = 0.0f;
}
vec3::vec3(float _vec)
{
	x = y = z = _vec;
}
vec3::vec3(vec2 _vec)
{
	x = _vec.x;
	y = _vec.y;
	z = 0.0f;
}
vec3::vec3(float _x, float _y)
{
	x = _x;
	y = _y;
	z = 0.0f;
}
vec3::vec3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

// rgba
rgba::rgba() {
	r = g = b = a = 1.0f;
}
rgba::rgba(float _rgb)
{
	r = g = b = _rgb;
	a = 1.0f;
}
rgba::rgba(float _rgb, float _a)
{
	r = g = b = _rgb;
	a = _a;
}
rgba::rgba(float _r, float _g, float _b)
{
	r = _r;
	g = _g;
	b = _b;
	a = 1.0f;
}	
rgba::rgba(float _r, float _g, float _b, float _a)
{
	r = _r;
	g = _g;
	b = _b;
	a = _a;
}

// bounding box
bbox::bbox() {
	min = max = vec2(0,0);
}
bbox::bbox(vec2 _min, vec2 _max)
{
	min = _min;
	max = _max;
}
