#pragma once

#include <glew.h>
#include <string>
#include <SnowPlainImage.h>

static GLuint loadPngDemo(const std::string& filename, int* outWidth, int* outHeight)
{
	bool alpha;

	int width, height;
	unsigned char* textureData = nullptr;
	ImageFormat imageFormat;
	bool error = loadPng(filename.c_str(), &width, &height, &imageFormat, &textureData);
	if (!error)
	{
		// Unable to load png file
		return 0;
	}

	int format;
	switch (imageFormat)
	{
	case ImageFormat::RGB:
		format = GL_RGB;
		break;
	case ImageFormat::RGBA:
		format = GL_RGBA;
		break;
	}

	GLuint result;
	glGenTextures(1, &result);
	glBindTexture(GL_TEXTURE_2D, result);
	glTexImage2D(GL_TEXTURE_2D, 0, format,
		width, height, 0, format, GL_UNSIGNED_BYTE, textureData);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	cleanUpPng();

	(*outWidth) = width;
	(*outHeight) = height;

	return result;
}