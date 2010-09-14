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
	ImageLoader() { }
	virtual ~ImageLoader();

	virtual void Load(std::string _path) { }
	virtual void Unload();

	void Bind();
	void Unbind();

	GLuint getTexture() { return im_texture.ptr; }
	unsigned getWidth() { return im_texture.width; }
	unsigned getHeight() { return im_texture.height; }

	// texture pointer
	void setTexture(Texture _tex) { im_texture = _tex; }

private:
	Texture im_texture;
	char _fmt;
};

#endif
