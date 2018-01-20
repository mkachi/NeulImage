#pragma once

#include "Time.h"
#include "Shader.h"
#include "Texture.h"
#include "MathPlus.h"
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Scene
{
public:
    Scene() {}
    virtual ~Scene() {}
    virtual void init() = 0;
    virtual void update(Time& time) = 0;
    virtual void render() = 0;
    virtual void destroy() = 0;

};