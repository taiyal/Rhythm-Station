#ifndef _IMAGE_LOADER_H_
#define _IMAGE_LOADER_H_

#include "RStation.h"
#include "TextureManager.h"
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

	void Bind();
	void Unbind();

	GLuint getTexture();
	unsigned getWidth();
	unsigned getHeight();

	void setTexture(Texture tex); // texture pointer

private:
	Texture im_texture;
	char _fmt;
};

#endif
