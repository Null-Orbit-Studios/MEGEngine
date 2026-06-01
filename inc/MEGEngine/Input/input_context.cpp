#include "MEGEngine/Input/input_context.h"
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
        Log(LogLevel::ERR, "InputReceiver subscription failed. Action '%s' not registered in InputSystem", actionName.c_str());
        return;
    }
    
    actionCallback ac = {
        .action = action,
        .callback = callback,
    };
    actionCallbacks.push_back(ac);
    Log(LogLevel::DBG, "Action '%s' linked to callback function", actionName.c_str());

    // if this context is currently active, subscribe the new action
    if (Engine::instance().inputSystem()->mapping().activeContext() == this) {
        Engine::instance().inputSystem()->subscribe(*ac.action, ac.callback);
    }
}