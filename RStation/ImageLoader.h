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
	
	virtual GLuint GetTexture();
	virtual void Unload();
	
	virtual unsigned GetWidth();
	virtual unsigned GetHeight();
	
	virtual void SetTexture(GLuint texture); // texture pointer
	virtual void SetWidth(unsigned width);
	virtual void SetHeight(unsigned height);
	
private:
	GLuint im_texture;
	char _fmt;
	unsigned im_width;
	unsigned im_height;
};

#endif