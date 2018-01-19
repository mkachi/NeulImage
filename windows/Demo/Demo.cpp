#include "Demo.h"

GLuint texture;
int _width, _height;

void Init(int screenWidth, int screenHeight)
{
	int width, height;
	bool alpha;

	const char* filename = "test.png";

	unsigned char* textureData = nullptr;
	bool result = loadPng(filename, width, height, alpha, &textureData);
	if (!result)
	{
		// Unable to load png file
		return;
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	GLint internalFormat = 3;
	GLenum format = GL_RGB8;
	if (alpha)
	{
		internalFormat = 4;
		format = GL_RGBA8;
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, 
		width, height, 0, format, GL_UNSIGNED_BYTE, textureData);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_FLAT);
}

void Update(float dt)
{	
}

void Render()
{

}

void Destroy()
{

}