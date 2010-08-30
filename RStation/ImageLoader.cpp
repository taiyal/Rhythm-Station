#include "ImageLoader.h"

// temporary macro
#define _MIN(x) (x ? x : 1)

ImageLoader::ImageLoader() {}
ImageLoader::~ImageLoader()
{
	this->Unbind();
	this->Unload();
}

GLuint ImageLoader::GetTexture()
{
	return im_texture;
}

void ImageLoader::SetTexture(GLuint _tex)
{
	im_texture = _tex;
}

// Load is done by children of ImageLoader - not here.

void ImageLoader::Unload()
{
	glDeleteTextures(1, &im_texture);
}

void ImageLoader::Bind()
{
	glBindTexture(GL_TEXTURE_2D, im_texture);
}

void ImageLoader::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned ImageLoader::GetWidth()
{
	return im_width;
}

unsigned ImageLoader::GetHeight()
{
	return im_height;
}

void ImageLoader::SetWidth(unsigned _width)
{
	im_width = _MIN(_width);
}

void ImageLoader::SetHeight(unsigned _height)
{
	im_height = _MIN(_height);
}

#undef _MIN