#ifndef _PNG_LOADER_H_
#define _PNG_LOADER_H_

#include "RStation.h"
#include "ImageLoader.h"

class PNGLoader : public ImageLoader
{
	void Load(std::string path);
	void Free();
};

#endif