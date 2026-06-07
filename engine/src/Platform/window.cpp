#include <stdexcept>

#include "GLFW/glfw3.h"

#include "MEGEngine/Platform/window.h"


struct Window::Impl {
    GLFWwindow* handle = nullptr;
};

struct Window::WindowHandle {
    GLFWwindow* ptr = nullptr;
};

Window::Window(std::string title, uint32_t width, uint32_t height) :
        _impl(new Impl()), _handle(new WindowHandle()), _windowTitle(title), _width(width), _height(height) {}

Window::~Window() {
    if (_handle->ptr)
        glfwDestroyWindow(_handle->ptr);

    glfwTerminate();
    delete _handle;
}

void Window::create() {
    // initialise GLFW and set some data for the window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // create window object

    // _impl->handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    _handle->ptr = glfwCreateWindow(_width, _height, _windowTitle.c_str(), nullptr, nullptr);
    if (!_handle->ptr) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    // _impl is deprecated but either _handle or _impl can be used
    _impl->handle = _handle->ptr;

    // apply actions to this window (make it the current context)
    glfwMakeContextCurrent(_handle->ptr);
}

void Window::pollEvents() {
    glfwPollEvents();
}
bool Window::shouldClose() const {
    return glfwWindowShouldClose(_handle->ptr);
}
void Window::display() {
    glfwSwapBuffers(_handle->ptr);
}

void Window::terminate() {
    glfwTerminate();
}

Window::Impl& Window::impl() {
    return *_impl;
}

Window::WindowHandle& Window::handle() {
    return *_handle;
}
