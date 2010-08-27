#ifndef _Type_H_
#define _Type_H_

#include <string>

// for GLuint and ILuint
#include <GL/glfw.h>

#ifdef _WIN32
	#include "stdint.h" // uint32 and such on Windows
#endif

#include <sstream>

namespace convert
{
	std::string toString(int);
	std::string toString(double);
	std::string toString(bool);
}

typedef uint32_t u32;
typedef int32_t i32;
typedef uint64_t u64;
typedef int64_t	i64;

typedef struct vec2 {
	vec2();
	vec2(float _xy);
	vec2(float _x, float _y);
	float x, y;
};

typedef struct vec3
{
	vec3();
	vec3(float _vec);
	vec3(vec2 _vec);
	vec3(float _x, float _y);
	vec3(float _x, float _y, float _z);
	float x, y, z;
};

// stubs, mostly.
typedef struct rgba
{
	rgba();
	rgba(float _rgb);
	rgba(float _rgb, float _a);
	rgba(float _r, float _g, float _b);
	rgba(float _r, float _g, float _b, float _a);
	float r, g, b, a;
};

typedef struct bbox
{
	bbox();
	bbox(vec2 _min, vec2 _max);
	vec2 min, max;
};
	
#endif
