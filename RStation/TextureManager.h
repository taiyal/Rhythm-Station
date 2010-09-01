#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_

#include "RStation.h"
#include <GL/glfw.h>

struct Texture
{
	std::string path;
	GLuint ptr;
	unsigned width, height;
};

namespace TextureManager
{
	Texture CheckForDuplicates(std::string _path);

	// TODO: add support for deleting a specific texture, instead of clearing them all.
	void addTexture(Texture _texture);
	void clear();
}

#endif
