#ifndef _IMAGE_LOADER_H_
#define _IMAGE_LOADER_H_

#include "RStation.h"
#include <GL/glfw.h>
#include "TextureManager.h"

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

	virtual void setTexture(Texture texture); // texture pointer

private:
	Texture im_texture;
	char _fmt;
};

#endif