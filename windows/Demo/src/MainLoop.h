#pragma once

#include <glew.h>
#include <wglew.h>
#include <glfw3.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Scene.h"
#include "Config.h"

class MainLoop
{
private:
    GLFWwindow* _window;
    Scene* _currentScene;

public:
    MainLoop() {}
    ~MainLoop() {}

    void init(Scene* scene);
    void loop();

};