#include "Demo.h"
#include <png/png.h>
// texture
GLuint shader;
GLuint texture;
int width, height;

// draw
GLuint vao;
mat4 projection;
mat4 model;

GLuint loadPngDemo(const char* filename)
{
	bool alpha;

	unsigned char* textureData = nullptr;
	ImageFormat imageFormat;
	bool error = loadPng(filename, &width, &height, &imageFormat, &textureData);
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

	return result;
}

void Init(int screenWidth, int screenHeight)
{
	texture = loadPngDemo("test.png");

	shader = loadShader("vertex.vert", "fragment.frag");

	projection = glm::ortho(0.0f, (float)screenWidth, (float)screenHeight, 0.0f, 0.0f, 100.0f);
	mat4 transform = glm::translate(model, vec3(0.0f, 0.0f, 0.0f));
	mat4 scale = glm::scale(model, vec3(width, height, 1.0f));
	model = transform * scale;

	glUseProgram(shader);
	shaderUniform(shader, "proj", projection);
	shaderUniform(shader, "model", model);
	InitDrawRect(screenWidth, screenHeight);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(vao);
}

void InitDrawRect(int screenWidth, int screenHeight)
{
	vec3 baseVertices[] =
	{
		vec3(1.0f, 1.0f, 0.0f),
		vec3(1.0f, 0.0f, 0.0f),
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f),
	};
	vec2 baseUV[] =
	{
		vec2(1.0f, 1.0f),
		vec2(1.0f, 0.0f),
		vec2(0.0f, 0.0f),
		vec2(0.0f, 1.0f)
	};
	GLuint baseIndices[] =
	{
		0, 1, 3,
		1, 2, 3
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(baseIndices), baseIndices, GL_STATIC_DRAW);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(baseVertices), baseVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid*)baseVertices);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, (GLvoid*)baseUV);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Update(float dt)
{	
}

void Render()
{
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Destroy()
{

}