
#include <cstring>

#include "MEGEngine/Input/input_system.h"
#include "MEGEngine/Core/engine.h"


void InputSystem::init() {
    Engine::instance().setInputSystem(this);
    _mapping.attachBus(_manager.bus());
}
InputAction& InputSystem::createAction(std::string name, InputAction::Type type) {
    _actions.push_back(std::make_unique<InputAction>(name, type));
    return *_actions.back();
}

std::vector<std::shared_ptr<InputAction>>& InputSystem::actions() {
    return _actions;
}

// Returns action if name matches one in the list. Returns null if not found
InputAction* InputSystem::findAction(std::string name) {
    if (this) {
        for (auto& action : _actions) {
            if (strcmp(action->name().c_str(), name.c_str()) == 0) {
                return action.get();
            }
        }
    }
    return nullptr;
}

std::shared_ptr<InputContext> InputSystem::createContext() {
    return std::make_shared<InputContext>();
}

void InputSystem::bind(InputContext& ctx, InputAction& action, InputSource src, ActionValue value) {
    ctx.addBinding(InputBinding{.action = &action, .source = src, .value = value});
}

void InputSystem::pushContext(std::shared_ptr<InputContext> ctx) {
    auto* activeCtx = _mapping.activeContext();
    if (activeCtx) {
        for (const auto& pair : activeCtx->actionCallbacks) {
            unsubscribe(*pair.action);
        }
    }

    _mapping.pushContext(ctx);

    for (const auto& pair : _mapping.activeContext()->actionCallbacks) {
        subscribe(*pair.action, pair.callback);
    }
}

void InputSystem::popContext() {
    auto* activeCtx = _mapping.activeContext();
    if (activeCtx) {
        for (const auto& pair : activeCtx->actionCallbacks) {
            unsubscribe(*pair.action);
        }
    }

    _mapping.popContext();

    activeCtx = _mapping.activeContext();
    if (activeCtx) {
        for (const auto& pair : activeCtx->actionCallbacks) {
            subscribe(*pair.action, pair.callback);
        }
    }
}

void InputSystem::subscribe(InputAction &action, PlayerActionBus::Callback cb) {
    _actionBus.subscribe(&action, std::move(cb));
}

void InputSystem::unsubscribe(InputAction &action) {
    _actionBus.unsubscribe(&action);
}

void InputSystem::update() {
    _mapping.beginFrame();
    _manager.update();
    _actionBus.publish(_mapping.states());
}
