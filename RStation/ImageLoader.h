#ifndef _IMAGE_LOADER_H_
#define _IMAGE_LOADER_H_

#include <GL/glfw.h>

/*
 * Generic image loading class for others to be based on.
 */

class ImageLoader
{
public:
	ImageLoader();
	virtual ~ImageLoader();
	
	GLuint GetTexture();
	void Unload();
	
	void Bind();
	void Unbind();
	
	unsigned GetWidth();
	unsigned GetHeight();
	
	void SetTexture(GLuint texture); // texture pointer
	void SetWidth(unsigned width);
	void SetHeight(unsigned height);
	
private:
	GLuint im_texture;
	char _fmt;
	unsigned im_width;
	unsigned im_height;
};

#endif