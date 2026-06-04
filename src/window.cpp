#include <stdexcept>

#include "GLFW/glfw3.h"

#include "MEGEngine/Core/window.h"


struct Window::Impl {
    GLFWwindow* handle = nullptr;
};

struct Window::WindowHandle {
    GLFWwindow* ptr = nullptr;
};

Window::Window() : _impl(new Impl()), _handle(new WindowHandle()) {}

Window::~Window() {
    if (_impl->handle)
        glfwDestroyWindow(_impl->handle);

    glfwTerminate();
    delete _impl;
}

void Window::create(const std::string& title, int width, int height) {
    // initialise GLFW and set some data for the window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // create window object

    // _impl->handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    _handle->ptr = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
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

Window::Impl& Window::impl() {
    return *_impl;
}

Window::WindowHandle& Window::handle() {
    return *_handle;
}
