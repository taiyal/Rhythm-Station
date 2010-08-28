#include "ImageLoader.h"

// temporary macro
#define _MIN(x) ((x > 0) ? x : 1)

void ImageLoader::SetWidth(unsigned _width)
{
	im_width = _MIN(_width);
}

void ImageLoader::SetHeight(unsigned _height)
{
	im_height = _MIN(_height);
}

#undef _MIN