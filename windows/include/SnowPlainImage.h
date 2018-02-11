#pragma once

#include "SubModule.h"

enum class ImageFormat
{
	RGB,
	RGBA,
};
extern "C"
{
	SP_SM bool loadPng(const char* filename, int* width, int* height, ImageFormat* format, unsigned char** data);
	SP_SM void cleanUpPng();

	SP_SM bool loadBmp(const char* filename, int* width, int* height, ImageFormat* format, unsigned char** data);
	SP_SM void cleanUpBmp();

	SP_SM bool loadTga(const char* filename, int* width, int* height, ImageFormat* format, unsigned char** data);
	SP_SM void cleanUpTga();

	SP_SM bool loadJpeg(const char* filename, int* width, int* heignt, ImageFormat* format, unsigned char** data);
	SP_SM void cleanUpJpeg();
}