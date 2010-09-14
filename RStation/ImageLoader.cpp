#include "ImageLoader.h"

ImageLoader::~ImageLoader()
{
	this->Unbind();
	this->Unload();
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
