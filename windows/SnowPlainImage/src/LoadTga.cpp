#include "SnowPlainImage.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string>

struct TgaHeader
{
	unsigned char	idLength;
	unsigned char	colorMapType;
	unsigned char	imageTypeCode;
	short			colourMapOrigin;
	short			colorMapLength;
	unsigned char	colorMapEntrySize;
	short			imageXOrigin;
	short			imageYOrigin;
	short			width;
	short			height;
	unsigned char	bitPerPixel;
	unsigned char	imageDescriptor;
};

static unsigned char* pixels = nullptr;

SP_SM bool loadTga(const char* filename, int* width, int* height, ImageFormat* format, unsigned char** data)
{
	FILE* fp = fopen(filename, "rb");
	if (fp == NULL)
	{
		// not found tga
		return false;
	}

	fseek(fp, -18, SEEK_END);
	char mimeType[17];
	fread(mimeType, 1, 17, fp);
	mimeType[16] = '\0';
	printf("%s\n", mimeType);
	if (strcmp(mimeType, "TRUEVISION-XFILE") != 0)
	{
		// is not tga
		return false;
	}
	fseek(fp, 0, SEEK_SET);

	unsigned char ucharTemp;
	fread(&ucharTemp, sizeof(unsigned char), 1, fp);
	fread(&ucharTemp, sizeof(unsigned char), 1, fp);
	TgaHeader header;
	fread(&header.imageTypeCode, sizeof(unsigned char), 1, fp);

	short shortTemp;
	fread(&shortTemp, sizeof(short), 1, fp);
	fread(&shortTemp, sizeof(short), 1, fp);
	fread(&ucharTemp, sizeof(unsigned char), 1, fp);
	fread(&shortTemp, sizeof(short), 1, fp);
	fread(&shortTemp, sizeof(short), 1, fp);

	fread(&header.width, sizeof(short), 1, fp);
	fread(&header.height, sizeof(short), 1, fp);
	fread(&header.bitPerPixel, sizeof(char), 1, fp);
	fread(&header.imageDescriptor, sizeof(char), 1, fp);

	(*width) = header.width;
	(*height) = header.height;

	int bytePerPixel = header.bitPerPixel / 8;
	if (header.bitPerPixel == 24)
	{
		(*format) = ImageFormat::RGB;
	}
	else if (header.bitPerPixel == 32)
	{
		(*format) = ImageFormat::RGBA;
	}
	else
	{
		// unsupported color type
		fclose(fp);
		return false;
	}
	int imageSize = header.width * header.height * bytePerPixel;
	pixels = new unsigned char[imageSize];
	fread(pixels, 1, imageSize, fp);
	fclose(fp);

	// swap the r and b values to get RGB (tga is BGR)
	unsigned char temp;
	int imageIndex = 0;
	for (int h = 0; h < header.height; ++h)
	{
		for (int w = 0; w < header.width; ++w)
		{
			temp = pixels[imageIndex];
			pixels[imageIndex] = pixels[imageIndex + 2];
			pixels[imageIndex + 2] = temp;
			imageIndex += bytePerPixel;
		}
		imageIndex += header.width % 4;
	}

	// tga vertical flip
	int flipIndex = imageIndex - header.width % 4 - header.width * bytePerPixel;
	imageIndex = 0;
	for (int h = 0; h < header.height / 2; ++h)
	{
		for (int w = 0; w < header.width; ++w)
		{
			for (int i = 0; i < bytePerPixel; ++i)
			{
				temp = pixels[imageIndex];
				pixels[imageIndex] = pixels[flipIndex];
				pixels[flipIndex] = temp;
				++flipIndex;
				++imageIndex;
			}
		}
		imageIndex += header.width % 4;
		flipIndex -= header.width * (bytePerPixel * 2);
		flipIndex -= header.width % 4;
	}
	(*data) = pixels;

	return true;
}

SP_SM void cleanUpTga()
{
	if (pixels != nullptr)
	{
		delete[] pixels;
	}
}