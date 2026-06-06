#include "MEGEngine/Platform/Input/input_receiver.h"
#include "MEGEngine/Core/engine.h"


void InputReceiver::linkActionCallback(std::string actionName, PlayerActionBus::Callback callback) {
    auto action = Engine::instance().inputSystem()->findAction(actionName);
    if (!action) {
        Log(LogLevel::ERR, "InputReceiver subscription failed. Action '%s' not registered in InputSystem", actionName.c_str());
        return;
    }
    
    ActionCallback ac = {
        .action = action,
        .callback = callback,
    };
    _actionCallbacks.push_back(ac);
    Log(LogLevel::DBG, "Action '%s' linked to callback function", actionName.c_str());

    // TODO: Instead publish an event - PlayerController belongs in game logic and user can implement subscription to that event
    // if this entity is currently possessed, update the player controller to subscribe the new action
    PlayerController pc = PlayerController::instance();
    if (pc.inputReceiver() == this) {
        pc.update();
    }
}

std::vector<ActionCallback>& InputReceiver::actionCallbacks() {
    return _actionCallbacks;
}
