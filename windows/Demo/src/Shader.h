#pragma once

#include <glew.h>
#include <string>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

template <typename T>
inline void safeDelete(T*& obj)
{
	if (obj != nullptr)
	{
		delete obj;
		obj = nullptr;
	}
}

static std::string loadFile(const std::string& filename)
{
    std::string result = "";
    std::ifstream stream(filename, std::ios::in);

    if (stream.is_open())
    {
        std::string line = "";
        while (getline(stream, line))
        {
            result += "\n" + line;
        }
    }
    stream.close();

    return result;
}

static GLuint loadShader(const std::string& vertex, const std::string& fragment, const std::string& geometry = "")
{
    bool geo = false;
    if (geometry != "")
    {
        geo = true;
    }
    GLuint result = glCreateProgram();

    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    std::string vertCode = loadFile(vertex);
    const char* nativeVertCode = vertCode.c_str();
    glShaderSource(vert, 1, &nativeVertCode, NULL);
    glCompileShader(vert);

    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragCode = loadFile(fragment);
    const char* nativeFragCode = fragCode.c_str();
    glShaderSource(frag, 1, &nativeFragCode, NULL);
    glCompileShader(frag);

    if (geo)
    {
        GLuint geome = glCreateShader(GL_GEOMETRY_SHADER);
        std::string geoCode = loadFile(geometry);
        const char* nativeGeoCode = geoCode.c_str();
        glShaderSource(geome, 1, &nativeGeoCode, NULL);
        glCompileShader(geome);
        glAttachShader(result, geome);
    }

    glAttachShader(result, vert);
    glAttachShader(result, frag);
    glLinkProgram(result);

    return result;
}

static void shaderUniform(GLuint shaderID, const char* name, mat4 m)
{
    GLint location = glGetUniformLocation(shaderID, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, &m[0].x);
}
static void shaderUniform(GLuint shaderID, const char* name, vec4 v)
{
    GLint location = glGetUniformLocation(shaderID, name);
    glUniform4f(location, v.r, v.g, v.b, v.a);
}
static void shaderUniform(GLuint shaderID, const char* name, vec2 v)
{
    GLint location = glGetUniformLocation(shaderID, name);
    glUniform2f(location, v.x, v.y);
}
static void shaderUniform(GLuint shaderID, const char* name, float depth)
{
    GLint location = glGetUniformLocation(shaderID, name);
    glUniform1f(location, depth);
}