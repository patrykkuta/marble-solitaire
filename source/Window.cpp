#include "Window.h"
#include "Screen.h"

bool Window::rightMouseButton = false;
bool Window::leftMouseButton = false;
double Window::lastMouseX = 0.0;
double Window::lastMouseY = 0.0;

Window::Window(int width, int height, const char* title) : _width(width), _height(height), _title(title) {
    // Initialize GLFW
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    // Set GLFW window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Create the GLFW window
    _window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!_window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    // Make the window's context current
    glfwMakeContextCurrent(_window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLEW");
    }

    // Set the swap interval for the window
    glfwSwapInterval(1);

    setMouseButtonCallback(Screen::mouse_button_callback_static);
    setCursorPosCallback(Screen::cursor_position_callback_static);
    setFramebufferSizeCallback(Screen::framebuffer_size_callback_static);
    setKeyCallback(Screen::key_callback_static);
}

Window::~Window() {
    // Destroy the GLFW window
    glfwDestroyWindow(_window);
    // Terminate GLFW
    glfwTerminate();
}

GLFWwindow* Window::getGLFWwindow() {
    return _window;
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(_window);
}

void Window::swapBuffers() {
    glfwSwapBuffers(_window);
}

void Window::pollEvents() {
    glfwPollEvents();
}

void Window::setMouseButtonCallback(void (*callback)(GLFWwindow*, int, int, int)) {
    glfwSetMouseButtonCallback(_window, callback);
}

void Window::setCursorPosCallback(void(*callback)(GLFWwindow*, double, double)) {
    glfwSetCursorPosCallback(_window, callback);
}

void Window::setFramebufferSizeCallback(void(*callback)(GLFWwindow*, int, int)) {
    glfwSetFramebufferSizeCallback(_window, callback);
}

void Window::setKeyCallback(void (*callback)(GLFWwindow*, int, int, int, int)) {
    glfwSetKeyCallback(_window, callback);
}

void Window::setScrollCallback(void(*callback)(GLFWwindow*, double, double))
{
    glfwSetScrollCallback(_window, callback);
}
