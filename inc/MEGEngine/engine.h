#ifndef MEGENGINEPROJECT_ENGINE_H
#define MEGENGINEPROJECT_ENGINE_H

#include "MEGEngine/common.h"
#include "MEGEngine/Input.h"
#include "MEGEngine/player_controller.h"
#include "MEGEngine/application.h"


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

    PlayerController* playerController() {
        return &_playerController;
    }

    void setApplication(Application* application) {
        _application = application;
    }

    Application& application() {
        return *_application;
    }

private:
    InputSystem* _inputSystem = nullptr;
    PlayerController _playerController;
    Application* _application = nullptr;
};

#endif //MEGENGINEPROJECT_ENGINE_H