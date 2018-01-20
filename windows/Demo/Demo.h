#pragma once

#ifdef _WINDOWS
#include <Windows.h>
#define GLEW_STATIC
#include <glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "Shader.h"

#include <SnowPlainImage.h>

GLuint loadPngDemo(const char* filename);

void Init(int screenWidth, int screenHeight);
void InitDrawRect(int screenWidth, int screenHeight);
void Update(float dt);
void Render();
void Destroy();