#include "FileManager.h"
#include "PNGLoader.h"
#include <png.h>
#include <GL/glfw.h>
#include "TextureManager.h"

void PNGLoader::Load(std::string _path)
{
	Texture dupe = TextureManager::CheckForDuplicates(_path);
	Texture tex;
	tex.loader = this;
	if( dupe.ptr )
	{
		this->setTexture(dupe);
		return;
	}
	png_structp png_ptr = NULL;
	png_infop info_ptr = NULL;
	png_bytep *row_pointers = NULL;
	int bitDepth, format;
	
	tex.path = _path;
	_path = FileManager::GetFile(_path);

	FILE *pngFile = fopen(_path.c_str(), "rb");

	if(!pngFile)
	{
		Log::Print("[PNGLoader::Load] File not found.");
		return;
	}

	png_byte sig[8];

	fread(&sig, 8, sizeof(png_byte), pngFile);
	rewind(pngFile); //so when we init io it won't bitch
	if(!png_check_sig(sig, 8))
		return;

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL,NULL,NULL);

	if(!png_ptr)
		return;

	if(setjmp(png_jmpbuf(png_ptr)))
		return;

	info_ptr = png_create_info_struct(png_ptr);

	if(!info_ptr)
		return;

	png_init_io(png_ptr, pngFile);
	png_read_info(png_ptr, info_ptr);
	bitDepth = png_get_bit_depth(png_ptr, info_ptr);
	format = png_get_color_type(png_ptr, info_ptr);

	if(format == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(png_ptr);

	if(format == PNG_COLOR_TYPE_GRAY && bitDepth < 8)
		png_set_expand_gray_1_2_4_to_8(png_ptr);

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
	tex.width = width;
	tex.height = height;

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
			ret = -1;
	};

	if(ret == -1)
	{
		if(png_ptr)
			png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		Log::Print("[PNGLoader::Load] File invalid. Is this really a PNG file?");
		return;
	}
	GLubyte *pixels = new GLubyte[tex.width * tex.height * ret];
	row_pointers = new png_bytep[tex.height];
	
	for(unsigned i = 0; i < tex.height; ++i)
		row_pointers[i] = (png_bytep)(pixels + (i * tex.width * ret));

	png_read_image(png_ptr, row_pointers);
	png_read_end(png_ptr, NULL);

	// upload texture to GPU
	glGenTextures(1, &tex.ptr); // make it
	glBindTexture(GL_TEXTURE_2D, tex.ptr); // bind it
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	GLuint glformat;
	switch(ret)
	{
		case 1:
			glformat = GL_LUMINANCE;
			break;
		case 2:
			glformat = GL_LUMINANCE_ALPHA;
			break;
		case 3:
			glformat = GL_RGB;
			break;
		case 4:
			glformat = GL_RGBA;
			break;
		default:
			glformat = 0; // this shouldn't happen.
			break;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, ret, tex.width, tex.height, 0, glformat, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, 0);

	this->setTexture(tex);

	// register this so we don't load it again.
	TextureManager::addTexture(tex);

	// cleanup
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);	
	fclose(pngFile);
	delete[] row_pointers;
	delete[] pixels;
}
