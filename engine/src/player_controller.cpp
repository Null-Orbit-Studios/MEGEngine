#include "MEGEngine/player_controller.h"
#include "MEGEngine/engine.h"

namespace MEGEngine {
    void PlayerController::setInputReceiver(InputReceiver* receiver) {

        // unsubscribe all actions of previous receiver
        if (inputReceiver) {
            for (const auto& pair : inputReceiver->actionCallbacks) {
                Engine::instance().inputSystem()->unsubscribe(*pair.action);
            }
        }

        // set new receiver and subscribe all actions
        inputReceiver = receiver;
        for (const auto& pair : inputReceiver->actionCallbacks) {
            Engine::instance().inputSystem()->subscribe(*pair.action, pair.callback);
        }
    }
} // MEGEngine