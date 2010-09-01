#include "ImageLoader.h"

// temporary macro
#define _MIN(x) (x ? x : 1)

ImageLoader::ImageLoader() {}
ImageLoader::~ImageLoader()
{
	this->Unbind();
	this->Unload();
}

GLuint ImageLoader::getTexture()
{
	return im_texture.ptr;
}

unsigned ImageLoader::getWidth()
{
	return im_texture.width;
}

unsigned ImageLoader::getHeight()
{
	return im_texture.height;
}

void ImageLoader::setTexture(Texture _tex)
{
	im_texture = _tex;
}

// Load is done by children of ImageLoader - not here.

void ImageLoader::Unload()
{
	glDeleteTextures(1, &im_texture.ptr);
}

void ImageLoader::Bind()
{
	glBindTexture(GL_TEXTURE_2D, im_texture.ptr);
}

void ImageLoader::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

#undef _MIN