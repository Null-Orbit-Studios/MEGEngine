#include "MEGEngine/Platform/Input/InputManager.hpp"


void InputManager::addDevice(std::unique_ptr<Base_InputDevice> device) {
    LOG_DBG("Device added to input manager");
    device->initialise(_bus);
    _devices.push_back(std::move(device));
}

void InputManager::update() {
    for (auto& device : _devices) {
        device->poll();
    }

    _bus.dispatch();
}
