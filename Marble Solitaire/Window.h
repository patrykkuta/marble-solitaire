#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

class Window {
private:
    GLFWwindow* _window;
    int _width;
    int _height;
    const char* _title;

public:
    static bool rightMouseButton;
    static bool leftMouseButton;
    static double lastMouseX;
    static double lastMouseY;

    Window(int width, int height, const char* title);
    ~Window();
    GLFWwindow* getGLFWwindow();
    bool shouldClose();
    void swapBuffers();
    void pollEvents();
    void setMouseButtonCallback(void (*callback)(GLFWwindow*, int, int, int));
    void setCursorPosCallback(void(*callback)(GLFWwindow*, double , double));
    void setFramebufferSizeCallback(void(*callback)(GLFWwindow*, int, int));

};