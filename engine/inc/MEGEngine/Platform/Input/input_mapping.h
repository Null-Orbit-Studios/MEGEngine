#ifndef MEGENGINEPROJECT_INPUT_MAPPING_H
#define MEGENGINEPROJECT_INPUT_MAPPING_H

#include <memory>
#include <unordered_map>

#include "MEGEngine/common.h"
#include "MEGEngine/Platform/Input/input_action.h"
#include "MEGEngine/Platform/Input/input_context.h"
#include "MEGEngine/Platform/Input/raw_input_event_bus.h"


class ENGINE_API InputMappingSystem {
public:
    void attachBus(RawInputEventBus& bus);
    void pushContext(std::shared_ptr<InputContext> context);
    void popContext();
    InputContext* activeContext();
    void beginFrame();
    const std::unordered_map<InputAction*, ActionState>& states() const;

private:
    void apply(InputAction* action, ActionValue v);
    void release(InputAction* action);
    void stop(InputAction* action, ActionValue v);
    void onKeyPressed(const KeyPressedEvent& e);
    void onKeyReleased(const KeyReleasedEvent& e);
    void onMouseMoved(const MouseMovedEvent& e);
    void onMouseStopped(const MouseStoppedEvent& e);

    std::stack<std::shared_ptr<InputContext>> _contexts;
    std::unordered_map<InputAction*, ActionState> _states;
};


#endif //MEGENGINEPROJECT_INPUT_MAPPING_H