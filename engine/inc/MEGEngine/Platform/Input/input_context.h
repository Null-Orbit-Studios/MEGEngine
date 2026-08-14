#ifndef MEGENGINEPROJECT_INPUT_CONTEXT_H
#define MEGENGINEPROJECT_INPUT_CONTEXT_H


#include "MEGEngine/common.h"
#include "MEGEngine/Platform/Input/input_events.h"
#include "MEGEngine/Platform/Input/input_action.h"
#include "MEGEngine/Platform/Input/player_action_bus.h"


class InputContext;
struct InputSource;
struct InputBinding;

struct ENGINE_API InputSource {
    enum class Type {
        KEY,
        MOUSE_DELTA
    };

    Type type;

    KeyCode key;
};

struct ENGINE_API InputBinding {
    InputAction* action; // can be null if no action is bound
    InputSource source; // cannot be null, must have a source that triggers it
    ActionValue value;
};

class ENGINE_API InputContext {
public:
    void addBinding(const InputBinding& binding);
    const std::vector<InputBinding>& bindings() const;

    void linkActionCallback(std::string actionName, PlayerActionBus::Callback callback);
    std::vector<ActionCallback>& actionCallbacks();

private:
    std::vector<InputBinding> _bindings;

    std::vector<ActionCallback> _actionCallbacks;
};


#endif //MEGENGINEPROJECT_INPUT_CONTEXT_H