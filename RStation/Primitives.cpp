#include "Primitives.h"
#include "MathUtils.h"
#include <GL/glfw.h>
#include <math.h>

void Primitive::Ngon(float _radius, unsigned _edges)
{
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0);
	float step = 360 / float(_edges);
	for(int i = 0; i <= _edges; i++)
	{
		float angle = radf(i*step);
		glVertex2f(cosf(angle)*_radius,sinf(angle)*_radius);
	}
	glEnd();
}

struct Vertex {
	Vertex() : x(0), y(0), z(0), u(0), v(0)
	{
		// hi
	}
	Vertex(float _x) : y(0), z(0), u(0), v(0)
	{
		x = _x;
	}
	Vertex(float _x, float _y) : z(0), u(0), v(0)
	{
		x = _x;
		y = _y;
	}
	Vertex(float _x, float _y, float _z) : u(0), v(0)
	{
		x = _x;
		y = _y;
		z = _z;
	}
	Vertex(float _x, float _y, float _z, float _u, float _v)
	{
		x = _x;
		y = _y;
		z = _z;
		u = _u;
		v = _v;
	}
	float x;
	float y;
	float z;
	
	float u;
	float v;
};

// TODO: vertex array
void Primitive::Quad(vec2 size)
{
	float cx = size.x * 0.5f;
	float cy = size.y * 0.5f;
	std::vector<Vertex> verts;
	Vertex back;
	// x, y, z, u, v
	verts.push_back(Vertex(-cx, cy,  0.0f, 0.0f, 1.0f));
	verts.push_back(Vertex( cx, cy,  0.0f, 1.0f, 1.0f));
	verts.push_back(Vertex( cx, -cy, 0.0f, 1.0f, 0.0f));
	verts.push_back(Vertex(-cx, -cy, 0.0f, 0.0f, 0.0f));
	glBegin(GL_QUADS);
	for ( unsigned i = 0; i<verts.size(); i++)
	{
		glTexCoord2f(verts[i].u, verts[i].v);
		glVertex3f(verts[i].x, verts[i].y, verts[i].z);
	}
	glEnd();
}
