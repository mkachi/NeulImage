#pragma once

#include "SubModule.h"
#include <stdio.h>

enum class ImageType
{
	Png,
	Bmp,
	Tga,
	Jpeg,
	Unknown,
};

enum class ColorFormat
{
	RGB,
	RGBA,
};

SP_SM const char* spGetError();

SP_SM bool spLoadImage(const char* filePath, int& width, int& height, ColorFormat& format, unsigned char*& pixels);
SP_SM bool spLoadImage(FILE*& file, int& width, int& height, ColorFormat& format, unsigned char*& pixels);
SP_SM bool spLoadPng(FILE*& file, int& width, int& height, ColorFormat& format, unsigned char*& pixels);
SP_SM bool spLoadBmp(FILE*& file, int& width, int& height, ColorFormat& format, unsigned char*& pixels);
SP_SM bool spLoadTga(FILE*& file, int& width, int& height, ColorFormat& format, unsigned char*& pixels);
SP_SM bool spLoadJpeg(FILE*& file, int& width, int& height, ColorFormat& format, unsigned char*& pixels);