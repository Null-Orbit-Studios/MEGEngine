#include "MEGEngine/Platform/Input/input_mapping.h"


void InputMappingSystem::attachBus(RawInputEventBus &bus) {
    // subscribe 'onKeyPressed' function to listen for key press events
    bus.subscribe<KeyPressedEvent>([this](auto& e) { onKeyPressed(e); });

    bus.subscribe<KeyReleasedEvent>([this](auto& e) { onKeyReleased(e); });

    bus.subscribe<MouseMovedEvent>([this](auto& e) { onMouseMoved(e); });

    bus.subscribe<MouseStoppedEvent>([this](auto& e) { onMouseStopped(e); });
}

void InputMappingSystem::pushContext(std::shared_ptr<InputContext> context) { _contexts.push(context); }

void InputMappingSystem::popContext() {
    if (!_contexts.empty())
        _contexts.pop();
}

InputContext* InputMappingSystem::activeContext() {
    if (_contexts.empty()) return nullptr;

    return _contexts.top().get();
}

void InputMappingSystem::beginFrame() {
    for (auto& [a, s] : _states) {
        s.started = false;
        s.completed = false;
    }
}

const std::unordered_map<InputAction*, ActionState>& InputMappingSystem::states() const {
    return _states;
}

void InputMappingSystem::apply(InputAction* action, KeyCode key, ActionValue v) {
    auto& state = _states[action];

    bool wasActive = state.ongoing;

    state.addValue(key, v);
    state.ongoing = true;

    if (!wasActive)
        state.started = true;
}

void InputMappingSystem::release(InputAction* action, KeyCode key) {
    auto& state = _states[action];
    state.removeValue(key);

    if (state.ongoing && state.valueIsEmpty())
    {
        state.ongoing = false;
        state.completed = true;
    }
}

void InputMappingSystem::stop(InputAction* action, ActionValue v) {
    auto& state = _states[action];

    if (state.ongoing)
    {
        state.ongoing = false;
        state.completed = true;
        state.addValue(KeyCode::UNKNOWN, v);
    }
}

void InputMappingSystem::onKeyPressed(const KeyPressedEvent& e) {
    if (_contexts.empty()) return;

    for (auto& b : _contexts.top()->bindings()) {
        if (b.source.type == InputSource::Type::KEY && b.source.key == e.key) {
            switch (b.action->type()) {
                case InputAction::Type::BOOL:
                    apply(b.action, e.key, ActionValue(b.value.asBool()));
                    break;
                case InputAction::Type::FLOAT:
                    apply(b.action, e.key, ActionValue(b.value.asFloat()));
                    break;
                case InputAction::Type::VEC2:
                    apply(b.action, e.key, ActionValue(b.value.asVec2()));
                    break;
            }
        }
    }
}

void InputMappingSystem::onKeyReleased(const KeyReleasedEvent& e) {
    if (_contexts.empty()) return;

    for (auto& b : _contexts.top()->bindings()) {
        if (b.source.type == InputSource::Type::KEY && b.source.key == e.key) {
            release(b.action, e.key);
        }
    }
}

void InputMappingSystem::onMouseMoved(const MouseMovedEvent& e) {
    if (_contexts.empty()) return;

    for (auto& b : _contexts.top()->bindings()) {
        if (b.source.type == InputSource::Type::MOUSE_DELTA) {
            apply(b.action, KeyCode::UNKNOWN, ActionValue(Vec2{e.dx, e.dy}));
        }
    }
}

void InputMappingSystem::onMouseStopped(const MouseStoppedEvent& e) {
    if (_contexts.empty()) return;

    for (auto& b : _contexts.top()->bindings()) {
        if (b.source.type == InputSource::Type::MOUSE_DELTA) {
            stop(b.action, ActionValue(Vec2(e.dx, e.dy)));
        }
    }
}
