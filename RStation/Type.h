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

// from stepmania.
struct vec2
{
public:
	vec2() {}
	vec2( float xy ) { x = y = xy; }
	vec2( const float * f )		{ x=f[0]; y=f[1]; }
	vec2( float x1, float y1 )	{ x=x1; y=y1; }
	
	// casting
	operator float* ()			{ return &x; };
	operator const float* () const		{ return &x; };
	
	// assignment operators
	vec2& operator += ( const vec2& other )	{ x+=other.x; y+=other.y; return *this; }
	vec2& operator -= ( const vec2& other )	{ x-=other.x; y-=other.y; return *this; }
	vec2& operator *= ( float f )			{ x*=f; y*=f; return *this; }
	vec2& operator /= ( float f )			{ x/=f; y/=f; return *this; }
	
	// binary operators
	vec2 operator + ( const vec2& other ) const	{ return vec2( x+other.x, y+other.y ); }
	vec2 operator - ( const vec2& other ) const	{ return vec2( x-other.x, y-other.y ); }
	vec2 operator * ( float f ) const			{ return vec2( x*f, y*f ); }
	vec2 operator / ( float f ) const			{ return vec2( x/f, y/f ); }
	
	friend vec2 operator * ( float f, const vec2& other )	{ return other*f; }
	
	float x, y;
};

struct vec3
{
public:
	vec3() {}
	vec3( float xyz ) { x = y = z = xyz; }
	vec3( const float * f )			{ x=f[0]; y=f[1]; z=f[2]; }
	vec3( float x1, float y1, float z1 )	{ x=x1; y=y1; z=z1; }
	
	// casting
	operator float* ()				{ return &x; };
	operator const float* () const			{ return &x; };
	
	// assignment operators
	vec3& operator += ( const vec3& other )	{ x+=other.x; y+=other.y; z+=other.z; return *this; }
	vec3& operator -= ( const vec3& other )	{ x-=other.x; y-=other.y; z-=other.z; return *this; }
	vec3& operator *= ( float f )			{ x*=f; y*=f; z*=f; return *this; }
	vec3& operator /= ( float f )			{ x/=f; y/=f; z/=f; return *this; }
	
	// binary operators
	vec3 operator + ( const vec3& other ) const	{ return vec3( x+other.x, y+other.y, z+other.z ); }
	vec3 operator - ( const vec3& other ) const	{ return vec3( x-other.x, y-other.y, z-other.z ); }
	vec3 operator * ( float f ) const			{ return vec3( x*f, y*f, z*f ); }
	vec3 operator / ( float f ) const			{ return vec3( x/f, y/f, z/f ); }
	
	friend vec3 operator * ( float f, const vec3& other )	{ return other*f; }
	
	float x, y, z;
};

struct rgba
{
public:
	rgba() {}
	rgba( float _rgb ) { r = g = b = _rgb; a = 1.0f; }
	rgba( float _rgb, float _a ) { r = g = b = _rgb; a = _a; }
	rgba( const float * f )				{ r=f[0]; g=f[1]; b=f[2]; a=f[3]; }
	rgba( float r1, float g1, float b1, float a1 )	{ r=r1; g=g1; b=b1; a=a1; }
	
	// casting
	operator float* ()					{ return &r; };
	operator const float* () const				{ return &r; };
	
	// assignment operators
	rgba& operator += ( const rgba& other )	{ r+=other.r; g+=other.g; b+=other.b; a+=other.a; return *this; }
	rgba& operator -= ( const rgba& other )	{ r-=other.r; g-=other.g; b-=other.b; a-=other.a; return *this; }
	rgba& operator *= ( float f )			{ r*=f; g*=f; b*=f; a*=f; return *this; }
	rgba& operator /= ( float f )			{ r/=f; g/=f; b/=f; a/=f; return *this; }
	
	// binary operators
	rgba operator + ( const rgba& other ) const	{ return rgba( r+other.r, g+other.g, b+other.b, a+other.a ); }
	rgba operator - ( const rgba& other ) const	{ return rgba( r-other.r, g-other.g, b-other.b, a-other.a ); }
	rgba operator * ( float f ) const			{ return rgba( r*f, g*f, b*f, a*f ); }
	rgba operator / ( float f ) const			{ return rgba( r/f, g/f, b/f, a/f ); }
	
	friend rgba operator * ( float f, const rgba& other )	{ return other*f; }
	
	float r, g, b, a;
};

#endif
