#pragma once

#include <glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <stack>

using namespace glm;

struct Vertex
{
	vec3 position;
	vec2 uv;

	Vertex(vec3 pos, vec2 u)
		: position(pos), uv(u)
	{   }
};

struct Material
{
	int materialID;
	GLuint shader;
	GLuint texture;
};

struct Sprite
{
	Material* material;
	vec3 position;
	vec2 size;
};

struct Batch
{
	int renderObjectCount = 0;
	Material* material;
	std::vector<Vertex> vertDatas;
	std::vector<GLuint> indices;
	GLuint vertexBuffer;
	GLuint indexBuffer;

	void add(const std::vector<Vertex>& vertices, const std::vector<GLuint>& index)
	{
		for (int i = 0; i < vertices.size(); ++i)
		{
			vertDatas.push_back(vertices[i]);
		}

		int offset = renderObjectCount * vertices.size();
		for (int i = 0; i < index.size(); ++i)
		{
			indices.push_back(index[i] + offset);
		}
		++renderObjectCount;
	}
};

class BatchRenderer
{
private:
	int currentID = -1;
	std::stack<Batch> _batches;

public:
	void addSprite(Sprite* sprite)
	{
		if (currentID != sprite->material->materialID)
		{
			currentID = sprite->material->materialID;
			_batches.push(Batch());
			_batches.top().material = sprite->material;
		}

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

		mat4 model;
		model = glm::translate(model, sprite->position);
		model = glm::scale(model, vec3(sprite->size.x, sprite->size.y, 1.0f));

		for (int i = 0; i < 4; ++i)
		{
			vec3 vert = VectorMultiple(model, baseVertices[i]);
			_batches.top().vertDatas.push_back(Vertex(vert, baseUV[i]));
		}

		int offset = _batches.top().renderObjectCount * _batches.top().vertDatas.size();
		for (int i = 0; i < 6; ++i)
		{
			_batches.top().indices.push_back(baseIndices[i] + offset);
		}
		++_batches.top().renderObjectCount;
	}

	void render(mat4 pv)
	{
		while (!_batches.empty())
		{
			Batch temp = _batches.top();

			setBatchShaderUniform(temp.material->shader, pv);
			// Bind vertex buffer
			glGenBuffers(1, &temp.vertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, temp.vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, temp.vertDatas.size() * sizeof(temp.vertDatas[0]), temp.vertDatas.data(), GL_DYNAMIC_DRAW);

			glGenBuffers(1, &temp.indexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, temp.indexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, temp.indices.size() * sizeof(GLuint), temp.indices.data(), GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (const GLvoid*)offsetof(Vertex, position));

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (const GLvoid*)offsetof(Vertex, uv));

			glBindTexture(GL_TEXTURE_2D, temp.material->texture);
			glDrawElements(GL_TRIANGLES, temp.indices.size(), GL_UNSIGNED_INT, 0);

			glDeleteBuffers(1, &temp.vertexBuffer);
			glDeleteBuffers(1, &temp.indexBuffer);
			_batches.pop();
		}
		currentID = -1;
	}

	void setBatchShaderUniform(GLuint shader, mat4 pv)
	{
		glUseProgram(shader);
		shaderUniform(shader, "ML_PV", pv);
		shaderUniform(shader, "ML_COLOR", vec4(1.0f, 1.0f, 1.0f, 1.0f));
	}
};