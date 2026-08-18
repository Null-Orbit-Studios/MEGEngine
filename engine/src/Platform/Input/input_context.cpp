#include "MEGEngine/Platform/Input/input_context.h"
#include "MEGEngine/Core/engine.h"

void InputContext::addBinding(const InputBinding& binding) {
    _bindings.push_back(binding);
}

const std::vector<InputBinding>& InputContext::bindings() const {
    return _bindings;
}

void InputContext::linkActionCallback(std::string actionName, PlayerActionBus::Callback callback) {
    auto action = Engine::instance().inputSystem()->findAction(actionName);
    if (!action) {
        LOG_ERR("InputReceiver subscription failed. Action '%s' not registered in InputSystem", actionName.c_str());
        return;
    }
    
    ActionCallback ac = {
        .action = action,
        .callback = callback,
    };
    _actionCallbacks.push_back(ac);
    LOG_DBG("Action '%s' linked to callback function", actionName.c_str());

    // if this context is currently active, subscribe the new action
    if (Engine::instance().inputSystem()->mapping().activeContext() == this) {
        Engine::instance().inputSystem()->subscribe(*ac.action, ac.callback);
    }
}

std::vector<ActionCallback>& InputContext::actionCallbacks() {
    return _actionCallbacks;
}