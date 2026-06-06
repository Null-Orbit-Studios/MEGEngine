#ifndef MEGENGINEPROJECT_INPUT_SYSTEM_H
#define MEGENGINEPROJECT_INPUT_SYSTEM_H

#include <memory>

#include "MEGEngine/common.h"
#include "MEGEngine/Core/Interfaces/IInput.h"
#include "MEGEngine/Platform/Input/player_action_bus.h"


class ENGINE_API InputSystem : IInput {
public:
    InputAction& createAction(std::string name, InputAction::Type type) override;
    std::vector<std::shared_ptr<InputAction>>& actions() override;
    InputAction* findAction(std::string name) override;
    std::shared_ptr<InputContext> createContext() override;
    void bind(InputContext& ctx, InputAction& action, InputSource src, ActionValue value = true) override;
    void pushContext(std::shared_ptr<InputContext> ctx) override;
    void popContext() override;
    void subscribe(InputAction& action, PlayerActionBus::Callback cb) override;
    void unsubscribe(InputAction& action) override;
    void update() override;
    InputManager& manager() override { return _manager; }
    InputMappingSystem& mapping() override { return _mapping; };
    void init() override;

private:
    InputManager _manager;
    InputMappingSystem _mapping;
    PlayerActionBus _actionBus;

    std::vector<std::shared_ptr<InputAction>> _actions;
};


#endif //MEGENGINEPROJECT_INPUT_SYSTEM_H