#pragma once

#include <glew.h>
#include <string>
#include <SnowPlainImage.h>

static GLuint loadImage(const std::string& filename, int& width, int& height)
{
	ColorFormat colorFormat;
	unsigned char* pixels = nullptr;
	bool error = spLoadImage(filename.c_str(), width, height, colorFormat, pixels);
	if (!error)
	{
		return 0;
	}

	int format;
	switch (colorFormat)
	{
	case ColorFormat::RGB:
		format = GL_RGB;
		break;
	case ColorFormat::RGBA:
		format = GL_RGBA;
		break;
	}

	GLuint result;
	glGenTextures(1, &result);
	glBindTexture(GL_TEXTURE_2D, result);
	glTexImage2D(GL_TEXTURE_2D, 0, format,
		width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	return result;
}