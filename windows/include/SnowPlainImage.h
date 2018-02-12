/*--
 *	SnowPlainImage
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

#pragma once

#include "SubModule.h"
#include <stdio.h>

/**
  *	@author M_Kachi
  *	@enum ImageType
  *	@brief Image formats
*/
enum class ImageType
{
	Png,
	Bmp,
	Tga,
	Jpeg,
	Unknown,
};

/**
	* @author M_Kachi
	* @enum ColorFormat
	* @brief Image color formats
*/
enum class ColorFormat
{
	RGB,
	RGBA,
};

/**
  *	@author M_Kachi
  *	@date 2018-02-13
  *	@brief The errors are stacked on the stack and pulled one by one.
  *	@return Error message
*/
SP_SM const char* spGetError();

/**
  *	@author M_Kachi
  *	@date 2018-02-13
  *	@brief Load image file.
  *	@param filePath - Image file path
  *	@param width - Variable to store image width
  *	@param height - Variable to store image height
  *	@param format - Variable to store image color format
  *	@param pixels - Variable to store image pixels
  *	@return Success | true, Failed | false
*/
SP_SM bool spLoadImage(const char* filePath, int& width, int& height, ColorFormat& format, unsigned char*& pixels);
/**
  *	@author M_Kachi
  *	@date 2018-02-13
  *	@brief Load image file.
  *	@param file - Image file pointer
  *	@param width - Variable to store image width
  *	@param height - Variable to store image height
  *	@param format - Variable to store image color format
  *	@param pixels - Variable to store image pixels
  *	@return Success | true, Failed | false
*/
SP_SM bool spLoadImage(FILE*& file, int& width, int& height, ColorFormat& format, unsigned char*& pixels);
/**
  *	@author M_Kachi
  *	@date 2018-02-13
  *	@brief Load png file.
  *	@param file - Image file pointer
  *	@param width - Variable to store image width
  *	@param height - Variable to store image height
  *	@param format - Variable to store image color format
  *	@param pixels - Variable to store image pixels
  *	@return Success | true, Failed | false
*/
SP_SM bool spLoadPng(FILE*& file, int& width, int& height, ColorFormat& format, unsigned char*& pixels);
/**
  *	@author M_Kachi
  *	@date 2018-02-13
  *	@brief Load bmp file.
  *	@param file - Image file pointer
  *	@param width - Variable to store image width
  *	@param height - Variable to store image height
  *	@param format - Variable to store image color format
  *	@param pixels - Variable to store image pixels
  *	@return Success | true, Failed | false
*/
SP_SM bool spLoadBmp(FILE*& file, int& width, int& height, ColorFormat& format, unsigned char*& pixels);
/**
  *	@author M_Kachi
  *	@date 2018-02-13
  *	@brief Load tga file.
  *	@param file - Image file pointer
  *	@param width - Variable to store image width
  *	@param height - Variable to store image height
  *	@param format - Variable to store image color format
  *	@param pixels - Variable to store image pixels
  *	@return Success | true, Failed | false
*/
SP_SM bool spLoadTga(FILE*& file, int& width, int& height, ColorFormat& format, unsigned char*& pixels);
/**
  *	@author M_Kachi
  *	@date 2018-02-13
  *	@brief Load jpeg file.
  *	@param file - Image file pointer
  *	@param width - Variable to store image width
  *	@param height - Variable to store image height
  *	@param format - Variable to store image color format
  *	@param pixels - Variable to store image pixels
  *	@return Success | true, Failed | false
*/
SP_SM bool spLoadJpeg(FILE*& file, int& width, int& height, ColorFormat& format, unsigned char*& pixels);