#include "SnowPlainImage.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct BitmapFileHeader
{
	unsigned short	type;
	unsigned long	size;
	unsigned short	reserved1;
	unsigned short	reserved2;
	unsigned long	offBits;
};

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

static FILE*			fp = nullptr;
static unsigned char*	rowData = nullptr;

SP_SM bool loadBmp(const char* filename, int* width, int* height, ImageFormat* format, unsigned char** data)
{
	fp = fopen(filename, "rb");
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
		return false;
	}

	BitmapInfoHeader infoHeader;
	fread(&infoHeader, 1, sizeof(BitmapInfoHeader), fp);
	fseek(fp, fileHeader.offBits, SEEK_SET);

	(*width) = infoHeader.width;
	(*height) = infoHeader.height;

	if (infoHeader.bitCount == 32)
	{
		(*format) = ImageFormat::BGRA;
	}
	else if (infoHeader.bitCount == 24)
	{
		(*format) = ImageFormat::BGR;
	}
	else
	{
		// unsupported color type
		fclose(fp);
		return false;
	}

	rowData = new unsigned char[infoHeader.sizeImage];
	fread(rowData, 1, infoHeader.sizeImage, fp);

	(*data) = rowData;
	return true;
}

SP_SM void cleanUpBmp()
{
	fclose(fp);
	delete[] rowData;
}