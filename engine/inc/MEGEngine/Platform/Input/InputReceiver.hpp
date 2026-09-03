#ifndef MEGENGINEPROJECT_INPUT_RECEIVER_H
#define MEGENGINEPROJECT_INPUT_RECEIVER_H

#include "MEGEngine/Common.hpp"
#include "MEGEngine/Core/Component.hpp"
#include "MEGEngine/Platform/Input/InputAction.hpp"
#include "MEGEngine/Platform/Input/PlayerActionBus.hpp"



// A component that acts as an interface to subscribe actions in the input system to callback functions
class ENGINE_API InputReceiver : public Component {
public:
    void linkActionCallback(std::string actionName, PlayerActionBus::Callback callback);
    std::vector<ActionCallback>& actionCallbacks();

private:
    std::vector<ActionCallback> _actionCallbacks;
};


#endif //MEGENGINEPROJECT_INPUT_RECEIVER_H