#include <GLFW/glfw3.h>
#include "MEGEngine/Platform/Input.hpp"
#include "MEGEngine/Core/Settings.hpp"

struct WindowImpl {
    GLFWwindow* handle = nullptr;
};

int toGLFW(InputMode mode) {
    switch (mode) {
        case InputMode::CURSOR:
            return GLFW_CURSOR;
        case InputMode::STICKY_KEYS:
            return GLFW_STICKY_KEYS;
        case InputMode::STICKY_MOUSE_BUTTONS:
            return GLFW_STICKY_MOUSE_BUTTONS;
        case InputMode::LOCK_KEY_MODS:
            return GLFW_LOCK_KEY_MODS;
        case InputMode::RAW_MOUSE_MOTION:
            return GLFW_RAW_MOUSE_MOTION;
        default:
            return -1;
    }
}

int toGLFW(InputModeValue value) {
    switch (value) {
        case InputModeValue::CURSOR_NORMAL:
            return GLFW_CURSOR_NORMAL;
        case InputModeValue::CURSOR_HIDDEN:
            return GLFW_CURSOR_HIDDEN;
        case InputModeValue::CURSOR_DISABLED:
            return GLFW_CURSOR_DISABLED;
        case InputModeValue::CURSOR_CAPTURED:
            return GLFW_CURSOR_CAPTURED;
        case InputModeValue::TRUE:
            return true;
        case InputModeValue::FALSE:
            return false;
        default:
            return -1;
    }
}

InputModeValue toMEG(int value) {
    switch (value) {
        case GLFW_CURSOR_NORMAL:
            return InputModeValue::CURSOR_NORMAL;
        case GLFW_CURSOR_HIDDEN:
            return InputModeValue::CURSOR_HIDDEN;
        case GLFW_CURSOR_DISABLED:
            return InputModeValue::CURSOR_DISABLED;
        case GLFW_CURSOR_CAPTURED:
            return InputModeValue::CURSOR_CAPTURED;
        case true:
            return InputModeValue::TRUE;
        case false:
            return InputModeValue::FALSE;
        default:
            return InputModeValue::VOID;
    }
}

void setCursorPosition(IWindow& window, float x, float y) {
    WindowImpl* glfwWindow = static_cast<WindowImpl*>(static_cast<void*>(&window.impl()));
    glfwSetCursorPos(glfwWindow->handle, x, y);
}
void setCursorPosition(IWindow& window, Vec2 pos) {
    WindowImpl* glfwWindow = static_cast<WindowImpl*>(static_cast<void*>(&window.impl()));
    Vec2 center = Vec2(Settings::instance().graphics().windowWidth/2, Settings::instance().graphics().windowHeight/2);
    LOG_DBG("Settings cursor position: %f, %f", center.x, center.y);
    glfwSetCursorPos(glfwWindow->handle, pos.x, pos.y);
}

Vec2 getCursorPosition(IWindow& window, Vec2* pos) {
    WindowImpl* glfwWindow = static_cast<WindowImpl*>(static_cast<void*>(&window.impl()));
    double x, y;
    glfwGetCursorPos(glfwWindow->handle, &x, &y);
    pos->x = x;
    pos->y = y;
    return *pos;
}

void setInputMode(IWindow& window, InputMode mode, InputModeValue value) {
    WindowImpl* glfwWindow = static_cast<WindowImpl*>(static_cast<void*>(&window.impl()));
    if (toGLFW(mode) < 0) {
        LOG_WRN("setInputMode(): InputMode provided is invalid");
        return;
    }
    if (toGLFW(value) < 0) {
        LOG_WRN("setInputMode(): InputModeValue provided is invalid");
        return;
    }
    glfwSetInputMode(glfwWindow->handle, toGLFW(mode), toGLFW(value));
}

InputModeValue ENGINE_API getInputMode(IWindow& window, InputMode mode) {
    WindowImpl* glfwWindow = static_cast<WindowImpl*>(static_cast<void*>(&window.impl()));
    return toMEG(glfwGetInputMode(glfwWindow->handle, toGLFW(mode)));
}