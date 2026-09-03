#ifndef MEGENGINEPROJECT_INPUT_DEVICE_H
#define MEGENGINEPROJECT_INPUT_DEVICE_H

#include <array>
#include <typeinfo>

#include "MEGEngine/Common.hpp"
#include "MEGEngine/Utils/Logger.hpp"


class ENGINE_API Base_InputDevice {
public:
    virtual ~Base_InputDevice() = default;

    virtual void initialise(class RawInputEventBus& bus) {
        LOG_DBG("Initialising device %s", typeid(*this).name());
        _bus = &bus;
    }

    virtual void poll() = 0;

protected:
    RawInputEventBus* _bus = nullptr;
};


class ENGINE_API KeyboardDevice : public Base_InputDevice {
public:
    KeyboardDevice(class IWindow* window) : _window(window) {}
    void poll() override;

private:
    IWindow* _window;

    // 349 is GLFW_KEY_LAST+1
    std::array<bool, 349> _previous{};
};

class ENGINE_API MouseDevice : public Base_InputDevice {
public:
    MouseDevice(class IWindow* window) : _window(window) {}
    void initialise(class RawInputEventBus& bus) override;
    void poll() override;

private:
    IWindow* _window;
    double _lastX = 0;
    double _lastY = 0;

    // 8 is GLFW_MOUSE_BUTTON_LAST+1
    std::array<bool, 8> _previous{};
    bool isMoving = false;
};

// TODO: add gamepad device for controller support

#endif //MEGENGINEPROJECT_INPUT_DEVICE_H