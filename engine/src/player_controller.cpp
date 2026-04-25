#include "MEGEngine/player_controller.h"
#include "MEGEngine/engine.h"

namespace MEGEngine {
    void PlayerController::setInputReceiver(InputReceiver* receiver) {
        inputReceiver = receiver;
        for (const auto& pair : inputReceiver->actionCallbacks) {
            Engine::instance().inputSystem()->subscribe(*pair.action, pair.callback);
        }
    }
} // MEGEngine