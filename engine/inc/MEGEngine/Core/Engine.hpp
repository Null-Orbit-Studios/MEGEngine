#ifndef MEGENGINEPROJECT_ENGINE_H
#define MEGENGINEPROJECT_ENGINE_H

#include "MEGEngine/Common.hpp"
#include "MEGEngine/Platform/Input.hpp"
#include "MEGEngine/Core/PlayerController.hpp"
#include "MEGEngine/Core/Application.hpp"

// TODO: none of this needed?
class ENGINE_API Engine {
    public:
    static Engine& instance() {
        static Engine instance;
        return instance;
    }

    void setInputSystem(InputSystem* inputSystem) {
        _inputSystem = inputSystem;
    }
    // Returns null if no input system is set. Make sure to set and initialise input system before use
    InputSystem* inputSystem() {
        return _inputSystem;
    }

    void setApplication(Application* application) {
        _application = application;
    }

    Application& application() {
        return *_application;
    }

private:
    InputSystem* _inputSystem = nullptr;
    Application* _application = nullptr;
};

#endif //MEGENGINEPROJECT_ENGINE_H