#include "SnowPlainImage.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#pragma pack(push, 2)
struct BitmapFileHeader
{
	unsigned short	type;
	unsigned long	size;
	unsigned short	reserved1;
	unsigned short	reserved2;
	unsigned long	offBits;
};
#pragma pack(pop)

struct BitmapInfoHeader
{
	unsigned long	size;
	long			width;
	long			height;
	unsigned short	planes;
	unsigned short	bitCount;
	unsigned long	compression;
	unsigned long	sizeImage;
	long			xPelsPerMeter;
	long			yPelsPerMeter;
	unsigned long	clrUsed;
	unsigned long	clrImportant;
};

static unsigned char*	rowData = nullptr;

SP_SM bool loadBmp(const char* filename, int* width, int* height, ImageFormat* format, unsigned char** data)
{
	FILE* fp = fopen(filename, "rb");
	if (fp == NULL)
	{
		// not found bmp
		return false;
	}

	BitmapFileHeader fileHeader;
	fread(&fileHeader, 1, sizeof(BitmapFileHeader), fp);
	if (fileHeader.type != 0x4D42)
	{
		// is not a bmp
		fclose(fp);
		return false;
	}


	BitmapInfoHeader infoHeader;
	fread(&infoHeader, 1, sizeof(BitmapInfoHeader), fp);
	fseek(fp, fileHeader.offBits, SEEK_SET);
	if (infoHeader.sizeImage == 0)
	{
		infoHeader.sizeImage = fileHeader.size - fileHeader.offBits;
	}

	(*width) = infoHeader.width;
	(*height) = infoHeader.height;

	int colorCount = 0;
	if (infoHeader.bitCount == 32)
	{
		(*format) = ImageFormat::RGBA;
		colorCount = 4;
	}
	else if (infoHeader.bitCount == 24)
	{
		(*format) = ImageFormat::RGB;
		colorCount = 3;
	}
	else
	{
		// unsupported color type
		fclose(fp);
		return false;
	}

	rowData = new unsigned char[infoHeader.sizeImage];
	fread(rowData, 1, infoHeader.sizeImage, fp);

	unsigned char temp;
	int imageIndex = 0;
	// swap the r and b values to get RGB (bitmap is BGR)
	for (int h = 0; h < infoHeader.height; ++h)
	{
		for (int w = 0; w < infoHeader.width; ++w)
		{
			temp = rowData[imageIndex];
			rowData[imageIndex] = rowData[imageIndex + 2];
			rowData[imageIndex + 2] = temp;
			imageIndex += colorCount;
		}
		imageIndex += infoHeader.width % 4;
	}

	// bitmap vertical flip
	int flipIndex = imageIndex - infoHeader.width % 4 - infoHeader.width * colorCount;
	imageIndex = 0;

	for (int h = 0; h < infoHeader.height / 2; ++h)
	{
		for (int w = 0; w < infoHeader.width; ++w)
		{
			for (int i = 0; i < colorCount; ++i)
			{
				temp = rowData[imageIndex];
				rowData[imageIndex] = rowData[flipIndex];
				rowData[flipIndex] = temp;
				++flipIndex;
				++imageIndex;
			}
		}
		imageIndex += infoHeader.width % 4;
		flipIndex -= infoHeader.width * (colorCount * 2);
		flipIndex -= infoHeader.width % 4;
	}
	fclose(fp);

	(*data) = rowData;

	return true;
}
SP_SM void cleanUpBmp()
{
	if (rowData != nullptr)
	{
		delete[] rowData;
	}
}