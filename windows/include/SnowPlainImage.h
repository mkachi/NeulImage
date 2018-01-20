#pragma once

#include "SPSubModule.h"

enum class ImageFormat
{
	RGB,
	RGBA,
};
extern "C"
{
	SP_SM bool loadPng(const char* filename, int* width, int* height, ImageFormat* format, unsigned char** data);
	SP_SM void cleanUpPng();
}