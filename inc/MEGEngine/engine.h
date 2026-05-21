#ifndef MEGENGINEPROJECT_ENGINE_H
#define MEGENGINEPROJECT_ENGINE_H

#include "MEGEngine/common.h"
#include "MEGEngine/input.h"
#include "MEGEngine/player_controller.h"


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

private:
    InputSystem* _inputSystem = nullptr;
    PlayerController _playerController;
};

#endif //MEGENGINEPROJECT_ENGINE_H