#ifndef MEGENGINE_IINPUT_SYSTEM_H
#define MEGENGINE_IINPUT_SYSTEM_H

#include <string>
#include <vector>
#include <memory>
#include "MEGEngine/Input/input_action.h"
#include "MEGEngine/Input/input_context.h"
#include "MEGEngine/Input/input_manager.h"
#include "MEGEngine/Input/input_mapping.h"

class IInputSystem {
public:
    virtual InputAction& createAction(std::string name, InputAction::Type type) = 0;
    virtual std::vector<std::shared_ptr<InputAction>>& actions() = 0;
    virtual InputAction* findAction(std::string name) = 0;
    virtual std::shared_ptr<InputContext> createContext() = 0;
    virtual void bind(InputContext& ctx, InputAction& action, InputSource src, ActionValue value = true) = 0;
    virtual void pushContext(std::shared_ptr<InputContext> ctx) = 0;
    virtual void popContext() = 0;
    virtual void subscribe(InputAction& action, PlayerActionBus::Callback cb) = 0;
    virtual void unsubscribe(InputAction& action) = 0;
    virtual void update() = 0;
    virtual InputManager& manager() = 0;
    virtual InputMappingSystem& mapping() = 0;
    virtual void init() = 0;
};

#endif