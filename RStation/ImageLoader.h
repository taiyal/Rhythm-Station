#ifndef _IMAGE_LOADER_H_
#define _IMAGE_LOADER_H_

/*
 * Generic image loading class for others to be based on.
 */

class ImageLoader
{
public:
	ImageLoader();
	virtual ~ImageLoader();
	virtual unsigned char Pixels();
	virtual unsigned Width();
	virtual unsigned Height();
	
	virtual void SetPixels(unsigned char* pixels[]);
	virtual void SetFormat(char fmt);
	virtual void SetWidth(unsigned width);
	virtual void SetHeight(unsigned height);
	
private:
	char _fmt;
	unsigned im_width;
	unsigned im_height;
};

#endif