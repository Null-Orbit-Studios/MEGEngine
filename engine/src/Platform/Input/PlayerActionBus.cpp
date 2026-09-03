#include "MEGEngine/Platform/Input/PlayerActionBus.hpp"
#include "MEGEngine/Platform/Input/InputAction.hpp"


void PlayerActionBus::subscribe(InputAction *action, Callback cb) {
    _listeners[action].push_back(cb);
}

void PlayerActionBus::unsubscribe(InputAction *action) {
    _listeners.erase(action);
}

void PlayerActionBus::publish(const std::unordered_map<InputAction *, ActionState> &states) {
    for (auto& [action, state] : states) {
        if (state.started || state.ongoing || state.completed) { // only publish if state is 'active'
            if (_listeners.count(action)) {
                for (auto& cb : _listeners[action]) {
                    cb(state);
                }
            }
        }
    }
}
