#include "PNGLoader.h"
#include <png.h>
#include <GL/glfw.h>

unsigned png(const char *filename)
{
	unsigned texture;
	png_structp png_ptr = NULL;
	png_infop info_ptr = NULL;
	png_bytep *row_pointers = NULL;
	int bitDepth, format;
	
	FILE *pngFile = fopen(filename, "rb");
	
	if(!pngFile)
		return 0;
	
	png_byte sig[8];
	
	fread(&sig, 8, sizeof(png_byte), pngFile);
	rewind(pngFile); //so when we init io it won't bitch
	if(!png_check_sig(sig, 8))
		return 0;
	
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL,NULL,NULL);
	
	if(!png_ptr)
		return 0;
	
	if(setjmp(png_jmpbuf(png_ptr)))
		return 0;
	
	info_ptr = png_create_info_struct(png_ptr);
	
	if(!info_ptr)
		return 0;
	
	png_init_io(png_ptr, pngFile);
	png_read_info(png_ptr, info_ptr);
	bitDepth = png_get_bit_depth(png_ptr, info_ptr);
	format = png_get_color_type(png_ptr, info_ptr);
	
	if(format == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(png_ptr);

	if(format == PNG_COLOR_TYPE_GRAY && bitDepth < 8)
		png_set_gray_1_2_4_to_8(png_ptr);

	if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(png_ptr);

	if(bitDepth == 16)
		png_set_strip_16(png_ptr);

	else if(bitDepth < 8)
		png_set_packing(png_ptr);

	png_read_update_info(png_ptr, info_ptr);
	png_uint_32 width, height;
	png_get_IHDR(png_ptr, info_ptr, &width, &height,
			 &bitDepth, &format, NULL, NULL, NULL);
	
	int ret;	
	switch(format)
	{
		case PNG_COLOR_TYPE_GRAY:
			ret = 1;
			break;
		case PNG_COLOR_TYPE_GRAY_ALPHA:
			ret = 2;
			break;
		case PNG_COLOR_TYPE_RGB:
			ret = 3;
			break;
		case PNG_COLOR_TYPE_RGB_ALPHA:
			ret = 4;
			break;
		default:
			ret = -1; // fucked
	};
	
	if(ret == -1)
	{
		if(png_ptr)
			png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		return 0;
	}
	
	GLubyte *pixels = (GLubyte *)malloc(sizeof(GLubyte) * (width * height * ret));
	row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * height);
	
	for(int i = 0; i < height; ++i)
	{
		row_pointers[i] = (png_bytep)(pixels + (i * width * ret));
	}
	
	png_read_image(png_ptr, row_pointers);
	png_read_end(png_ptr, NULL);
	
	
	
	// make it
	glGenTextures(1, &texture);
	// bind it
	glBindTexture(GL_TEXTURE_2D, texture);
	// stretch it
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	// technologic - I MEAN
	
	// here we have problems
	GLuint glformat;
	(ret == 4) ? ( glformat = GL_RGBA ) : 0;
	(ret == 3) ? ( glformat = GL_RGB ) : 0;
	(ret == 2) ? ( glformat = GL_LUMINANCE_ALPHA ) : 0;
	(ret == 1) ? ( glformat = GL_LUMINANCE ) : 0;
	
	glTexImage2D(GL_TEXTURE_2D, 0, ret, width, height, 0, glformat, GL_UNSIGNED_BYTE, pixels);
	
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	
	fclose(pngFile);
	free(row_pointers);
	free(pixels);
	
	return texture;
}
