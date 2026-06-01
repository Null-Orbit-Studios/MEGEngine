#ifndef MEGENGINEPROJECT_INPUT_CONTEXT_H
#define MEGENGINEPROJECT_INPUT_CONTEXT_H


#include "MEGEngine/common.h"
#include "MEGEngine/Input/input_events.h"
#include "MEGEngine/Input/input_action.h"
#include "MEGEngine/Input/player_action_bus.h"


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
    float scale = 1.0f;
};

class ENGINE_API InputContext {
public:
    void addBinding(const InputBinding& binding);
    const std::vector<InputBinding>& bindings() const;

    void linkActionCallback(std::string actionName, PlayerActionBus::Callback callback);

private:
    // TODO: add bindingsMap with string name as key and binding as value
    std::vector<InputBinding> _bindings;

    // used for persistent bindings which are associated with a context, not an input receiver
    friend class InputSystem;
    struct actionCallback {
        InputAction* action;
        PlayerActionBus::Callback callback;
    };

    std::vector<actionCallback> actionCallbacks;
};


#endif //MEGENGINEPROJECT_INPUT_CONTEXT_H