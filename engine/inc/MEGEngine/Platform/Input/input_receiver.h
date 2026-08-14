#ifndef MEGENGINEPROJECT_INPUT_RECEIVER_H
#define MEGENGINEPROJECT_INPUT_RECEIVER_H

#include "MEGEngine/common.h"
#include "MEGEngine/Core/component.h"
#include "MEGEngine/Platform/Input/input_action.h"
#include "MEGEngine/Platform/Input/player_action_bus.h"



// A component that acts as an interface to subscribe actions in the input system to callback functions
class ENGINE_API InputReceiver : public Component {
public:
    void linkActionCallback(std::string actionName, PlayerActionBus::Callback callback);
    std::vector<ActionCallback>& actionCallbacks();

private:
    std::vector<ActionCallback> _actionCallbacks;
};


#endif //MEGENGINEPROJECT_INPUT_RECEIVER_H