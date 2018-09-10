/*--
 *	NeulImage
 *	Copyright (C) 2018, ¸ÀÄ«Ä¡ (mkachi@naver.com)
 *	
 *	This library is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU Lesser General Public
 *	License as published by the Free Software Foundation; either
 *	version 2.1 of the License, or (at your option) any later version.
 *	
 *	This library is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *	Lesser General Public License for more details.
 *	
 *	You should have received a copy of the GNU Lesser General Public
 *	License along with this library; if not, write to the Free Software
 *	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 *	USA
*/

#include "NeulImage.h"
#include "png/png.h"
#include "jpeg/jpeglib.h"
#include <stdlib.h>
#include <string.h>

#if _DEBUG
#define ERROR(_LOG_) writeError(_LOG_)
#else
#define ERROR(_LOG_)
#endif

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

typedef struct Log_def
{
	const char* log;
	struct Log_def* next;
}Log;

typedef struct jpeg_decompress_struct	jpeg_info;
typedef struct jpeg_error_mgr			jpeg_err;

static Log* head = nullptr;
static Log* tail = nullptr;

void writeError(const char* log)
{
	Log* node = (Log*)malloc(sizeof(Log));
	node->log = log;
	node->next = nullptr;

	if (head == nullptr)
	{
		head = node;
		tail = head;
	}
	else
	{
		tail->next = node;
	}
}
NL_SM const char* niGetImageError()
{
	if (head != nullptr)
	{
		Log* node = head;
		const char* result = node->log;
		head = node->next;
		free(node);
		return result;
	}
	return "none";
}

bool checkPng(FILE* file)
{
	if (file == NULL)
	{
		return false;
	}
	png_byte header[8];
	fread(header, 1, 8, file);
	fseek(file, 0, SEEK_SET);

	if (png_sig_cmp(header, 0, 8) == 0)
	{
		return true;
	}
	return false;
}
bool checkBmp(FILE* file)
{
	if (file == NULL)
	{
		return false;
	}
	unsigned short header;
	fread(&header, 1, 2, file);
	fseek(file, 0, SEEK_SET);

	if (header == 0x4D42)
	{
		return true;
	}
	return false;
}
bool checkTga(FILE* file)
{
	if (file == NULL)
	{
		return false;
	}
	fseek(file, -18, SEEK_END);

	char header[17];
	fread(header, 1, 17, file);
	header[16] = '\0';
	fseek(file, 0, SEEK_SET);

	if (strcmp(header, "TRUEVISION-XFILE") == 0)
	{
		return true;
	}
	return false;
}
bool checkJpeg(FILE* file)
{
	if (file == NULL)
	{
		return false;
	}
	unsigned short header;
	fread(&header, 2, 1, file);
	fseek(file, 0, SEEK_SET);

	if (header == 0xD8FF)
	{
		return true;
	}
	return false;
}

ImageType formatCheck(FILE* file)
{
	if (checkPng(file))
	{
		return ImageType::Png;
	}
	else if (checkBmp(file))
	{
		return ImageType::Bmp;
	}
	else if (checkTga(file))
	{
		return ImageType::Tga;
	}
	else if (checkJpeg(file))
	{
		return ImageType::Jpeg;
	}
	return ImageType::Unknown;
}

NL_SM bool niLoadImage(const char* filePath, int& width, int& height, ColorFormat& format, unsigned char*& pixels)
{
	FILE* file = fopen(filePath, "rb");
	switch (formatCheck(file))
	{
	case ImageType::Png:	return niLoadPng(file, width, height, format, pixels);
	case ImageType::Bmp:	return niLoadBmp(file, width, height, format, pixels);
	case ImageType::Tga:	return niLoadTga(file, width, height, format, pixels);
	case ImageType::Jpeg:	return niLoadJpeg(file, width, height, format, pixels);
	default:
	case ImageType::Unknown:
		ERROR("Unsupported image format.");
		return false;
	}
	return false;
}
NL_SM bool niLoadImage(FILE*& file, int& width, int& height, ColorFormat& format, unsigned char*& pixels)
{
	switch (formatCheck(file))
	{
	case ImageType::Png:	return niLoadPng(file, width, height, format, pixels);
	case ImageType::Bmp:	return niLoadBmp(file, width, height, format, pixels);
	case ImageType::Tga:	return niLoadTga(file, width, height, format, pixels);
	case ImageType::Jpeg:	return niLoadJpeg(file, width, height, format, pixels);
	default:
	case ImageType::Unknown:
		ERROR("Unsupported image format.");
		return false;
	}
	return false;
}

NL_SM bool niLoadPng(FILE*& file, int& width, int& height, ColorFormat& format, unsigned char*& pixels)
{
	fseek(file, 8, SEEK_SET);

	png_struct* png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png)
	{
		ERROR("Failed create png_struct.");
		fclose(file);
		return false;
	}

	png_info* info = png_create_info_struct(png);
	if (!info)
	{
		ERROR("Failed create png_info.");
		png_destroy_read_struct(&png, NULL, NULL);
		fclose(file);
		return false;
	}

	png_info* endInfo = png_create_info_struct(png);
	if (!endInfo)
	{
		ERROR("Failed create png_info.");
		png_destroy_read_struct(&png, &info, NULL);
		fclose(file);
		return false;
	}

	if (setjmp(png_jmpbuf(png)))
	{
		ERROR("Error from libpng.");
		png_destroy_read_struct(&png, &info, &endInfo);
		fclose(file);
		return false;
	}

	png_init_io(png, file);
	png_set_sig_bytes(png, 8);
	png_read_info(png, info);

	int bitDepth, colorType;
	png_uint_32 tempWidth, tempHeight;

	png_get_IHDR(png, info, &tempWidth, &tempHeight, &bitDepth, &colorType, NULL, NULL, NULL);

	width = tempWidth;
	height = tempHeight;

	if (bitDepth != 8)
	{
		ERROR("Unsupported bit depth, must be 8.");
		return false;
	}

	switch (colorType)
	{
	case PNG_COLOR_TYPE_RGB:
		format = ColorFormat::RGB;
		break;
	case PNG_COLOR_TYPE_RGB_ALPHA:
		format = ColorFormat::RGBA;
		break;
	default:
		ERROR("Unknown color format.");
		return false;
	}
	png_read_update_info(png, info);
	png_size_t rowBytes = png_get_rowbytes(png, info);
	rowBytes += 3 - ((rowBytes - 1) % 4);

	pixels = new png_byte[rowBytes * tempHeight * sizeof(png_byte) + 15];
	if (pixels == nullptr)
	{
		ERROR("Failed allocate memory for png pixel data.");
		png_destroy_read_struct(&png, &info, &endInfo);
		fclose(file);
		return false;
	}

	png_byte** rowPtr = new png_byte*[tempHeight * sizeof(png_byte*)];
	if (rowPtr == nullptr)
	{
		ERROR("Failed allocate memory for rowPtr.");
		png_destroy_read_struct(&png, &info, &endInfo);
		free(pixels);
		fclose(file);
		return false;
	}

	for (unsigned int i = 0; i < tempHeight; ++i)
	{
		rowPtr[i] = pixels + i * rowBytes;
	}
	png_read_image(png, rowPtr);
	fclose(file);
	png_destroy_read_struct(&png, &info, &endInfo);

	if (rowPtr != nullptr)
	{
		delete[] rowPtr;
		rowPtr = nullptr;
	}

	return true;
}
NL_SM bool niLoadBmp(FILE*& file, int& width, int& height, ColorFormat& format, unsigned char*& pixels)
{
	BitmapFileHeader fileHeader;
	fread(&fileHeader, 1, sizeof(BitmapFileHeader), file);

	BitmapInfoHeader infoHeader;
	fread(&infoHeader, 1, sizeof(BitmapInfoHeader), file);
	fseek(file, fileHeader.offBits, SEEK_SET);
	if (infoHeader.sizeImage == 0)
	{
		infoHeader.sizeImage = fileHeader.size - fileHeader.offBits;
	}

	width = infoHeader.width;
	height = infoHeader.height;

	int colorCount = 0;
	if (infoHeader.bitCount == 32)
	{
		format = ColorFormat::RGBA;
		colorCount = 4;
	}
	else if (infoHeader.bitCount == 24)
	{
		format = ColorFormat::RGB;
		colorCount = 3;
	}
	else
	{
		ERROR("Unknown color format.");
		fclose(file);
		return false;
	}

	pixels = new unsigned char[infoHeader.sizeImage];
	fread(pixels, 1, infoHeader.sizeImage, file);

	unsigned char temp;
	int imageIndex = 0;

	for (int h = 0; h < infoHeader.height; ++h)
	{
		for (int w = 0; w < infoHeader.width; ++w)
		{
			temp = pixels[imageIndex];
			pixels[imageIndex] = pixels[imageIndex + 2];
			pixels[imageIndex + 2] = temp;
			imageIndex += colorCount;
		}
		imageIndex += infoHeader.width % 4;
	}

	int flipIndex = imageIndex - infoHeader.width % 4 - infoHeader.width * colorCount;
	imageIndex = 0;

	for (int h = 0; h < infoHeader.height / 2; ++h)
	{
		for (int w = 0; w < infoHeader.width; ++w)
		{
			for (int i = 0; i < colorCount; ++i)
			{
				temp = pixels[imageIndex];
				pixels[imageIndex] = pixels[flipIndex];
				pixels[flipIndex] = temp;
				++flipIndex;
				++imageIndex;
			}
		}
		imageIndex += infoHeader.width % 4;
		flipIndex -= infoHeader.width * (colorCount * 2);
		flipIndex -= infoHeader.width % 4;
	}
	fclose(file);

	return true;
}
NL_SM bool niLoadTga(FILE*& file, int& width, int& height, ColorFormat& format, unsigned char*& pixels)
{
	unsigned char ucharTemp;
	fread(&ucharTemp, sizeof(unsigned char), 1, file);
	fread(&ucharTemp, sizeof(unsigned char), 1, file);
	TgaHeader header;
	fread(&header.imageTypeCode, sizeof(unsigned char), 1, file);

	short shortTemp;
	fread(&shortTemp, sizeof(short), 1, file);
	fread(&shortTemp, sizeof(short), 1, file);
	fread(&ucharTemp, sizeof(unsigned char), 1, file);
	fread(&shortTemp, sizeof(short), 1, file);
	fread(&shortTemp, sizeof(short), 1, file);

	fread(&header.width, sizeof(short), 1, file);
	fread(&header.height, sizeof(short), 1, file);
	fread(&header.bitPerPixel, sizeof(char), 1, file);
	fread(&header.imageDescriptor, sizeof(char), 1, file);

	width = header.width;
	height = header.height;

	int bytePerPixel = header.bitPerPixel / 8;
	if (header.bitPerPixel == 24)
	{
		format = ColorFormat::RGB;
	}
	else if (header.bitPerPixel == 32)
	{
		format = ColorFormat::RGBA;
	}
	else
	{
		ERROR("Unknown color format.");
		fclose(file);
		return false;
	}
	int imageSize = header.width * header.height * bytePerPixel;
	pixels = new unsigned char[imageSize];
	fread(pixels, 1, imageSize, file);
	fclose(file);

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

	return true;
}
NL_SM bool niLoadJpeg(FILE*& file, int& width, int& height, ColorFormat& format, unsigned char*& pixels)
{
	jpeg_info	info;
	jpeg_err	error;
	info.err = jpeg_std_error(&error);
	jpeg_create_decompress(&info);

	jpeg_stdio_src(&info, file);
	jpeg_read_header(&info, TRUE);
	info.do_fancy_upsampling = FALSE;

	jpeg_start_decompress(&info);
	width = info.output_width;
	height = info.output_height;

	if (info.num_components != 3)
	{
		ERROR("Unknown color format.");
		return false;
	}
	format = ColorFormat::RGB;

	int bitPerPixel = info.num_components * 8;
	int dataSize = info.output_width * info.output_height * info.num_components;
	pixels = new unsigned char[dataSize];

	int line = 0;
	unsigned char* ptr1 = pixels;
	unsigned char** ptr2 = &ptr1;
	while (info.output_scanline < info.output_height)
	{
		line = jpeg_read_scanlines(&info, ptr2, 1);
		*ptr2 += line * info.num_components * info.output_width;
	}
	jpeg_finish_decompress(&info);
	jpeg_destroy_decompress(&info);
	fclose(file);

	return true;
}