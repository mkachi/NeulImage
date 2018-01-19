#include "SnowPlainImage.h"
#include <stdlib.h>
#include <string.h>
#include "png/png.h"

SP_SM bool loadPng(const char* name, int& outWidth, int& outHeight, bool& outHasAlpha, unsigned char** outData)
{
	png_struct* png;
	png_info*	info;
	unsigned int sigRead = 0;
	int colorType, interlaceType;
	FILE* fp = NULL;
	fp = fopen(name, "rb");
	if (fp == NULL)
	{
		return false;
	}

	png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png == NULL)
	{
		fclose(fp);
		return false;
	}

	info = png_create_info_struct(png);
	if (info == NULL)
	{
		fclose(fp);
		png_destroy_read_struct(&png, NULL, NULL);
		return false;
	}

	if (setjmp(png_jmpbuf(png)))
	{
		png_destroy_read_struct(&png, &info, NULL);
		fclose(fp);
		return false;
	}

	png_init_io(png, fp);
	png_set_sig_bytes(png, sigRead);
	png_read_png(png, info, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

	png_uint_32 width, height;
	int bitDepth;
	png_get_IHDR(png, info,
		&width, &height,
		&bitDepth, &colorType, &interlaceType, NULL, NULL);

	outWidth = width;
	outHeight = height;

	png_size_t rowBytes = png_get_rowbytes(png, info);
	*outData = (unsigned char*)malloc(rowBytes * outHeight);

	png_bytepp rowPtr = png_get_rows(png, info);

	for (unsigned int i = 0; i < outHeight; ++i)
	{
		memcpy(*outData + (rowBytes * (outHeight - 1 - i)), rowPtr[i], rowBytes);
	//	rowPtr[outHeight - 1 - i] = (*outData) + i * rowBytes;
	}
	png_destroy_read_struct(&png, &info, NULL);

	fclose(fp);
	return true;
}