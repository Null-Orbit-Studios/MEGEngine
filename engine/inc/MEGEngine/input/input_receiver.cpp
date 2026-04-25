#include "MEGEngine/input/input_receiver.h"
#include "MEGEngine/engine.h"

namespace MEGEngine {
    void InputReceiver::linkActionCallback(std::string actionName, PlayerActionBus::Callback callback) {
        if (auto action = Engine::instance().inputSystem()->findAction(actionName)) {
            actionCallback ac = {
                .action = action,
                .callback = callback,
            };
            actionCallbacks.push_back(ac);
            Log(LogLevel::DBG, "Action '%s' linked to callback function", actionName.c_str());
        } else {
            Log(LogLevel::ERR, "InputReceiver subscription failed. Action '%s' not registered in InputSystem", actionName.c_str());
        }
    }
} // MEGEngine