#pragma once

#ifdef _WINDOWS
#include <Windows.h>
#define GLEW_STATIC
#include <glew.h>
#include <wglew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#endif

#include <SnowPlainImage.h>

void Init(int screenWidth, int screenHeight);
void Update(float dt);
void Render();
void Destroy();