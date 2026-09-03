#include <GLFW/glfw3.h>

#include "MEGEngine/Platform/Input/InputDevice.hpp"
#include "MEGEngine/Platform/Input/RawInputEventBus.hpp"
#include "MEGEngine/Platform/Window.hpp"
#include "GLFWKeyTranslator.hpp"


struct WindowImpl {
    GLFWwindow* handle = nullptr;
};

void KeyboardDevice::poll() {
    WindowImpl* glfwWindow = static_cast<WindowImpl*>(static_cast<void*>(&_window->impl()));
    for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; ++key) {
        bool isDown = glfwGetKey(glfwWindow->handle, key) == GLFW_PRESS;

        if (isDown && !_previous[key]) {
            _bus->queueEvent(KeyPressedEvent{.key = GLFWKeyTranslator::translate(key)});
        }
        else if (!isDown && _previous[key]) {
            _bus->queueEvent(KeyReleasedEvent{.key = GLFWKeyTranslator::translate(key)});
        }

        _previous[key] = isDown;
    }
}

void MouseDevice::initialise(RawInputEventBus& bus) {
    WindowImpl* glfwWindow = static_cast<WindowImpl*>(static_cast<void*>(&_window->impl()));
    _bus = &bus;
    glfwGetCursorPos(glfwWindow->handle, &_lastX, &_lastY);
}
void MouseDevice::poll() {
    WindowImpl* glfwWindow = static_cast<WindowImpl*>(static_cast<void*>(&_window->impl()));

    double x, y;
    glfwGetCursorPos(glfwWindow->handle, &x, &y);

    float dx = float(x - _lastX);
    float dy = float(y - _lastY);

    if (dx != 0 || dy != 0) {
        _bus->queueEvent(MouseMovedEvent{.x = float(x), .y = float(y), .dx = dx, .dy = dy});
        isMoving = true;
    }
    else if ((dx == 0 && dy == 0) && isMoving) {
        _bus->queueEvent(MouseStoppedEvent{.x = float(x), .y = float(y)});
        isMoving = false;
    }

    _lastX = x;
    _lastY = y;

    for (int button = GLFW_MOUSE_BUTTON_1; button <= GLFW_MOUSE_BUTTON_LAST; ++button) {
        bool isDown = glfwGetMouseButton(glfwWindow->handle, button) == GLFW_PRESS;

        if (isDown && !_previous[button]) {
            _bus->queueEvent(KeyPressedEvent{.key = GLFWKeyTranslator::translate(button)});
        }
        else if (!isDown && _previous[button]) {
            _bus->queueEvent(KeyReleasedEvent{.key = GLFWKeyTranslator::translate(button)});
        }

        _previous[button] = isDown;
    }
}
