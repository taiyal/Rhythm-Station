#ifndef _IMAGE_LOADER_H_
#define _IMAGE_LOADER_H_

/*
 * Generic image loading class for others to be based on.
 */

class ImageLoader
{
public:
	void Free();
	
	unsigned char Pixels();
	unsigned Width();
	unsigned Height();
	
	void SetPixels(unsigned char* pixels[]);
	void SetWidth(unsigned width);
	void SetHeight(unsigned height);
	
private:
	char** pixels;
	
	unsigned width;
	unsigned height;
};

#endif