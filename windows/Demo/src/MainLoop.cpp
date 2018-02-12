#include "MainLoop.h"

void MainLoop::init(Scene* scene)
{
    glfwInit();
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);

    _window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "SnowPlainImage Demo", nullptr, nullptr);
    glfwMakeContextCurrent(_window);
    glewExperimental = GL_TRUE;

    glewInit();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glFrontFace(GL_CCW);
    _currentScene = scene;
}

void MainLoop::loop()
{
    Time time;
    _currentScene->init();

    while (!glfwWindowShouldClose(_window))
    {
        time.Tick();
        _currentScene->update(time);

        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _currentScene->render();

        glfwSwapBuffers(_window);

        if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            break;
        }
    }
    _currentScene->destroy();
    delete _currentScene;

    glfwDestroyWindow(_window);
    glfwTerminate();
}
