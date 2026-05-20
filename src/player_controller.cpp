#include "MEGEngine/player_controller.h"
#include "MEGEngine/engine.h"

namespace MEGEngine {
    void PlayerController::possess(Entity& player) {
        auto receiver = player.getComponent<InputReceiver>();
        if (!receiver) {
            Log(LogLevel::ERR, "Cannot possess entity as it does not have an InputReceiver component");
            return;
        }

        // unsubscribe all actions of previous receiver
        if (_inputReceiver) {
            for (const auto& pair : _inputReceiver->actionCallbacks) {
                Engine::instance().inputSystem()->unsubscribe(*pair.action);
            }
        }


        // set new receiver and subscribe all actions
        _inputReceiver = receiver;
        for (const auto& pair : _inputReceiver->actionCallbacks) {
            Engine::instance().inputSystem()->subscribe(*pair.action, pair.callback);
        }

        Log(LogLevel::DBG, "Possessed new entity: %s", typeid(player).name());

    }

    void PlayerController::update() {
        if (_inputReceiver) {
            // unsubscribe all actions of receiver
            for (const auto& pair : _inputReceiver->actionCallbacks) {
                Engine::instance().inputSystem()->unsubscribe(*pair.action);
            }

            // subscribe to all actions of input receiver
            for (const auto& pair : _inputReceiver->actionCallbacks) {
                Engine::instance().inputSystem()->subscribe(*pair.action, pair.callback);
            }
        }
    }

    InputReceiver* PlayerController::inputReceiver() {
        return _inputReceiver;
    }
} // MEGEngine