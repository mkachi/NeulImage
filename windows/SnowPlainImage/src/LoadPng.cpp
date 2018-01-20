#include "SnowPlainImage.h"
#include <stdlib.h>
#include <string.h>
#include "png/png.h"

static FILE*		fp = nullptr;
static png_struct*	png = nullptr;
static png_info*	info = nullptr;
static png_info*	endInfo = nullptr;
static png_byte*	imageData = nullptr;
static png_byte**	rowPtr = nullptr;

SP_SM bool loadPng(const char* filename, int* width, int* height, ImageFormat* format, unsigned char** data)
{
	png_byte header[8];
	fp = fopen(filename, "rb");
	if (fp == NULL)
	{
		// not found png
		return false;
	}
	fread(header, 1, 8, fp);

	if (png_sig_cmp(header, 0, 8))
	{
		// is not a png
		fclose(fp);
		return false;
	}

	png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png)
	{
		// png_create_read_struct returned 0
		fclose(fp);
		return false;
	}

	info = png_create_info_struct(png);
	if (!info)
	{
		// png_create_info_struct returned 0
		png_destroy_read_struct(&png, NULL, NULL);
		fclose(fp);
		return false;
	}

	endInfo = png_create_info_struct(png);
	if (!endInfo)
	{
		// png_create_info_struct returned 0
		png_destroy_read_struct(&png, &info, NULL);
		fclose(fp);
		return false;
	}

	if (setjmp(png_jmpbuf(png)))
	{
		// error from libpng
		png_destroy_read_struct(&png, &info, &endInfo);
		fclose(fp);
		return false;
	}

	png_init_io(png, fp);
	png_set_sig_bytes(png, 8);
	png_read_info(png, info);

	int bitDepth, colorType;
	png_uint_32 tempWidth, tempHeight;

	png_get_IHDR(png, info, &tempWidth, &tempHeight, &bitDepth, &colorType, NULL, NULL, NULL);

	(*width) = tempWidth;
	(*height) = tempHeight;

	if (bitDepth != 8)
	{
		// unsupported bit depth, must be 8
		return false;
	}

	switch (colorType)
	{
	case PNG_COLOR_TYPE_RGB:
		(*format) = ImageFormat::RGB;
		break;
	case PNG_COLOR_TYPE_RGB_ALPHA:
		(*format) = ImageFormat::RGBA;
		break;
	default:
		// unknown libpng color type
		return false;
	}
	png_read_update_info(png, info);
	png_size_t rowBytes = png_get_rowbytes(png, info);
	rowBytes += 3 - ((rowBytes - 1) % 4);

	imageData = (png_byte*)malloc(rowBytes * tempHeight * sizeof(png_byte) + 15);
	if (imageData == NULL)
	{
		// could not allocate memory for PNG image data
		png_destroy_read_struct(&png, &info, &endInfo);
		fclose(fp);
		return false;
	}

	rowPtr = (png_byte**)malloc(tempHeight * sizeof(png_byte*));
	if (rowPtr == NULL)
	{
		// could not allocate memory for PNG row pointers
		png_destroy_read_struct(&png, &info, &endInfo);
		free(imageData);
		fclose(fp);
		return false;
	}

	for (unsigned int i = 0; i < tempHeight; ++i)
	{
	//	rowPtr[tempHeight - 1 - i] = imageData + i * rowBytes;
		rowPtr[i] = imageData + i * rowBytes;
	}
	png_read_image(png, rowPtr);

	(*data) = imageData;

	return true;
}

SP_SM void cleanUpPng()
{
	png_destroy_read_struct(&png, &info, &endInfo);
	free(imageData);
	free(rowPtr);
	fclose(fp);
}