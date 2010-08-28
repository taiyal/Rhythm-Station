#include "ImageLoader.h"

// temporary macro
#define _MIN(x) ((x > 0) ? x : 1)

ImageLoader::ImageLoader() {}
ImageLoader::~ImageLoader() {}

GLuint ImageLoader::GetTexture()
{
	return im_texture;
}

void ImageLoader::SetTexture(GLuint _tex)
{
	im_texture = _tex;
}

void ImageLoader::Unload()
{
	glDeleteTextures(1, &im_texture);
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