#include "SnowPlainImage.h"
#include <stdio.h>
#include "jpeg/jpeglib.h"
#include "jpeg/jerror.h"

typedef struct jpeg_decompress_struct jpeg_info;
typedef struct jpeg_error_mgr jpeg_err;

static unsigned char* pixels = nullptr;

SP_SM bool loadJpeg(const char* filename, int* width, int* height, ImageFormat* format, unsigned char** data)
{
	FILE* fp = fopen(filename, "rb");
	if (fp == NULL)
	{
		// not found jpeg
		return false;
	}

	unsigned short mimeType;
	fread(&mimeType, 2, 1, fp);
	if (mimeType != 0xD8FF)
	{
		// is not jpeg
		return false;
	}
	fseek(fp, 0, SEEK_SET);

	jpeg_info	info;
	jpeg_err	error;
	info.err = jpeg_std_error(&error);
	jpeg_create_decompress(&info);

	jpeg_stdio_src(&info, fp);
	jpeg_read_header(&info, TRUE);
	info.do_fancy_upsampling = FALSE;

	jpeg_start_decompress(&info);
	(*width) = info.output_width;
	(*height) = info.output_height;

	if (info.num_components != 3)
	{
		// unsupported color type
		return false;
	}
	(*format) = ImageFormat::RGB;

	int bitPerPixel = info.num_components * 8;
	int dataSize = info.output_width * info.output_height * info.num_components;
	pixels = new unsigned char[dataSize];

	int line = 0;
	unsigned char* ptr1 = pixels;
	unsigned char** ptr2 = &ptr1;
	while (info.output_scanline < info.output_height)
	{
		line = jpeg_read_scanlines(&info, ptr2, 1);
		*ptr2 += line * info.num_components * info.output_width;
	}
	jpeg_finish_decompress(&info);
	jpeg_destroy_decompress(&info);
	fclose(fp);

	(*data) = pixels;

	return true;
}

SP_SM void cleanUpJpeg()
{
	if (pixels != nullptr)
	{
		delete[] pixels;
		pixels = nullptr;
	}
}