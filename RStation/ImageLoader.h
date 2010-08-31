#ifndef _IMAGE_LOADER_H_
#define _IMAGE_LOADER_H_

#include "RStation.h"
#include <GL/glfw.h>

/*
 * Generic image loading class for others to be based on.
 */

class ImageLoader
{
public:
	ImageLoader();
	virtual ~ImageLoader();

	virtual void Load(std::string _path) { }
	virtual void Unload();

	virtual void Bind();
	virtual void Unbind();

	virtual GLuint getTexture();
	virtual unsigned getWidth();
	virtual unsigned getHeight();

	virtual void setTexture(GLuint texture); // texture pointer
	virtual void setWidth(unsigned width);
	virtual void setHeight(unsigned height);

private:
	GLuint im_texture;
	char _fmt;
	unsigned im_width;
	unsigned im_height;
};

#endif