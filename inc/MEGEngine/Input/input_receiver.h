#ifndef MEGENGINEPROJECT_INPUT_RECEIVER_H
#define MEGENGINEPROJECT_INPUT_RECEIVER_H

#include "MEGEngine/common.h"
#include "MEGEngine/component.h"
#include "MEGEngine/Input.h"



// A component that acts as an interface to subscribe actions in the input system to callback functions
class ENGINE_API InputReceiver : public Component {
public:
    void linkActionCallback(std::string actionName, PlayerActionBus::Callback callback);
protected:

private:
    friend class PlayerController;
    struct actionCallback {
        InputAction* action;
        PlayerActionBus::Callback callback;
    };

    // accessed by PlayerController (friend class) to subscribe to actions when this component's parent entity gets possessed
    std::vector<actionCallback> actionCallbacks;
};


#endif //MEGENGINEPROJECT_INPUT_RECEIVER_H